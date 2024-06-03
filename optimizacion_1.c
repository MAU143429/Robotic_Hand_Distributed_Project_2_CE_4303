#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

#define MANAGER 0
#define TAG 1

// Estructura del nodo para almacenar una palabra y su concurrencia
typedef struct Node {
    char *word;
    int count;
    struct Node *next;
} Node;

// Función para crear un nuevo nodo
Node* createNode(char *word) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->word = strdup(word);
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

// Función para agregar una palabra a la lista
void addWord(Node **head, char *word) {
    Node *current = *head;
    Node *previous = NULL;

    // Verificar duplicados por mayúsculas
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }

    // Buscar si la palabra ya está en la lista
    while (current != NULL && strcmp(current->word, word) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        // Si la palabra no está en la lista, agregar un nuevo nodo
        Node *newNode = createNode(word);
        if (previous == NULL) {
            *head = newNode;
        } else {
            previous->next = newNode;
        }
    } else {
        // Si la palabra ya está en la lista, incrementar el conteo
        current->count++;
    }
}



// Función para escribir la lista de palabras y sus conteos en un archivo
void writeFile(Node *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Node *current = head;
    while (current != NULL) {
        fprintf(file, "%s: %d\n", current->word, current->count);
        current = current->next;
    }

    fclose(file);
}

// Función para liberar la memoria de la lista
void freeList(Node *head) {
    Node *current = head;
    Node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current->word);
        free(current);
        current = nextNode;
    }
}


void readBuffer(Node **head, const char *buffer) {
    const char *delimiter = " \t\n"; // Delimitadores para palabras
    char *word = strtok(strdup(buffer), delimiter); // Duplicar buffer para evitar modificarlo
    while (word != NULL) {
        addWord(head, word);
        word = strtok(NULL, delimiter);
    }
}

char* saveToBuffer(Node *head) {
    size_t bufferSize = 1024;
    size_t offset = 0;
    char *buffer = (char *)malloc(bufferSize);
    if (buffer == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    Node *current = head;
    while (current != NULL) {
        // Calcula el tamaño necesario para la cadena actual
        size_t needed = snprintf(NULL, 0, "%s: %d\n", current->word, current->count);
        if (offset + needed + 1 > bufferSize) {
            // Redimensiona el buffer si es necesario
            bufferSize *= 2;
            buffer = (char *)realloc(buffer, bufferSize);
            if (buffer == NULL) {
                perror("Error reallocating memory");
                exit(EXIT_FAILURE);
            }
        }
        // Agrega la cadena al buffer
        offset += snprintf(buffer + offset, bufferSize - offset, "%s: %d\n", current->word, current->count);
        current = current->next;
    }

    return buffer;
}

int main(int argc, char *argv[]) {
    Node *head = NULL;

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* if (size != 4) {
        if (rank == MANAGER) {
            fprintf(stderr, "Este programa necesita 4 procesos.\n");
        }
        MPI_Finalize();
        return EXIT_FAILURE;
    } */

    int file_size, chunk_size;
    char *buffer = NULL;

    FILE *file = fopen("ca.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    chunk_size = file_size / size;

    buffer = (char *)malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    // Ajustar los tamaños de los chunks para no cortar palabras
    int lengths[size];
    int displs[size];
    displs[0] = 0;
    for (int i = 0; i < size; i++) {
        int end = (i == size - 1) ? file_size : displs[i] + chunk_size;
        while (end < file_size && !isspace(buffer[end])) {
            end++;
        }
        lengths[i] = end - displs[i];
        if (i < size - 1) {
            displs[i + 1] = end;
        }
    }

    int recv_length;
    char *local_chunk = (char *)malloc(lengths[rank] + 1);
    MPI_Scatter(lengths, 1, MPI_INT, &recv_length, 1, MPI_INT, MANAGER, MPI_COMM_WORLD);
    MPI_Scatterv(buffer, lengths, displs, MPI_CHAR, local_chunk, recv_length, MPI_CHAR, MANAGER, MPI_COMM_WORLD);
    local_chunk[recv_length] = '\0';

    //Quitar es rank==0 y ponerlo abajo
    if(rank==0){
        printf("Hola soy master trabajando\n");
        Node *head0 = NULL;
        readBuffer(&head0,local_chunk);
    
        char *buffer0= saveToBuffer(head0);
        int local_lengths_0 = strlen(buffer0);
        printf("Tamaño_del_buffer_0:%d\n",local_lengths_0);

        printf("Chunk_del_buffer_0:%s\n",buffer0);

        free(buffer0);
        freeList(head0);

    }else if(rank==1){
        Node *head1 = NULL;

        printf("Hola soy esclavo 1\n");

        readBuffer(&head1,local_chunk);

        char *buffer1 = saveToBuffer(head1);

        //printf("BUffer1:%s\n", buffer1);

        int local_lengths_1 = strlen(buffer1);

        MPI_Send(&local_lengths_1, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        MPI_Send(buffer1, local_lengths_1, MPI_CHAR, 0,TAG, MPI_COMM_WORLD);


        free(buffer1);
        freeList(head1);

    }else if(rank==2){
        Node *head2 = NULL;

        printf("Hola soy esclavo 2\n");
        readBuffer(&head2,local_chunk);
        
        char *buffer2 = saveToBuffer(head2);

        //printf("BUffer2:%s\n", buffer2);

        int local_lengths_2 = strlen(buffer2);

        MPI_Send(&local_lengths_2, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        MPI_Send(buffer2, local_lengths_2, MPI_CHAR, 0,TAG, MPI_COMM_WORLD);



        free(buffer2);
        freeList(head2);

        
    }else if(rank==3){
        Node *head3 = NULL;
        printf("Hola soy esclavo 3\n");
        readBuffer(&head3,local_chunk);

        char *buffer3 = saveToBuffer(head3);


        int local_lengths_3 = strlen(buffer3);

        MPI_Send(&local_lengths_3, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        MPI_Send(buffer3, local_lengths_3, MPI_CHAR, 0,TAG, MPI_COMM_WORLD);

        free(buffer3);
        freeList(head3);
        
    }


    if (rank==0){
        int local_lengths_1,local_lengths_2,local_lengths_3;
        MPI_Recv(&local_lengths_1,1,MPI_INT,1,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(&local_lengths_2,1,MPI_INT,2,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(&local_lengths_3,1,MPI_INT,3,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

        char *buffer_1 = (char *)malloc(local_lengths_1 +1 );
        char *buffer_2 = (char *)malloc(local_lengths_2 +1);
        char *buffer_3 = (char *)malloc(local_lengths_3 +1);

        MPI_Recv(buffer_1, local_lengths_1, MPI_CHAR, 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(buffer_2, local_lengths_2, MPI_CHAR, 2, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(buffer_3, local_lengths_3, MPI_CHAR, 3, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);     

        buffer_1[local_lengths_1] = '\0';
        buffer_2[local_lengths_2] = '\0';
        buffer_3[local_lengths_3] = '\0';

        printf("Tamaño_de_buffer_1:%d\n",local_lengths_1);
        printf("Tamaño_de_buffer_2:%d\n",local_lengths_2);
        printf("Tamaño_de_buffer_3:%d\n",local_lengths_3);

        printf("Chunk_del_buffer_1:%s\n",buffer_1);
        printf("Chunk_del_buffer_2:%s\n",buffer_2);
        printf("Chunk_del_buffer_3:%s\n",buffer_3);



        free(buffer_1);
        free(buffer_2);
        free(buffer_3);  
    }

   
    free(buffer);
    free(local_chunk);
    MPI_Finalize();
    return 0;
}