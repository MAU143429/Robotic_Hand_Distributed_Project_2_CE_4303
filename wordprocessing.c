#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

#define MANAGER 0
#define TAG 1

#define LONGITUD_ALFABETO 26
#define INICIO_ALFABETO_MAYUSCULAS 65
#define INICIO_ALFABETO_MINUSCULAS 97
#define MAXIMA_LONGITUD_CADENA 10000
#define MOD(i, n) (i % n + n) % n // Calcular módulo positivo


const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",
        *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


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

//------------------------------------Parte de Seguiridad---------------------------------

// Funcion para obtener el valor entero de un carácter
int ord(char c) {
    return (int)c;
}

// Funcion que recibe un mensaje a cifrar y un búfer en donde pondrá el resultado, a partir de las rotaciones indicadas
void cifrar(const char *mensaje, char *destino, int rotaciones) {
    /* Recorrer cadena */
    int i = 0;
    while (mensaje[i]) {
        char caracterActual = mensaje[i];
        int posicionOriginal = ord(caracterActual);
        if (!isalpha(caracterActual)) {
            destino[i] = caracterActual;
            i++;
            continue; // Ir a la siguiente iteración; por eso arriba aumentamos a i
        }
        if (isupper(caracterActual)) {
            destino[i] = alfabetoMayusculas[(posicionOriginal - INICIO_ALFABETO_MAYUSCULAS + rotaciones) % LONGITUD_ALFABETO];
        } else {
            destino[i] = alfabetoMinusculas[(posicionOriginal - INICIO_ALFABETO_MINUSCULAS + rotaciones) % LONGITUD_ALFABETO];
        }
        i++;
    }
    destino[i] = '\0'; // Agregar el terminador nulo al final
}

// Funcion que recibe un mensaje a descifrar y un búfer en donde pondrá el resultado, a partir de las rotaciones indicadas
void descifrar(const char *mensaje, char *destino, int rotaciones) {
    /* Recorrer cadena */
    int i = 0;
    while (mensaje[i]) {
        char caracterActual = mensaje[i];
        int posicionOriginal = ord(caracterActual);
        if (!isalpha(caracterActual)) {
            destino[i] = caracterActual;
            i++;
            continue; // Ir a la siguiente iteración; por eso arriba aumentamos a i
        }
        if (isupper(caracterActual)) {
            destino[i] = alfabetoMayusculas[MOD(posicionOriginal - INICIO_ALFABETO_MAYUSCULAS - rotaciones, LONGITUD_ALFABETO)];
        } else {
            destino[i] = alfabetoMinusculas[MOD(posicionOriginal - INICIO_ALFABETO_MINUSCULAS - rotaciones, LONGITUD_ALFABETO)];
        }
        i++;
    }
    destino[i] = '\0'; // Agregar el terminador nulo al final
}


// Función para escribir la lista de palabras y sus conteos en un archivo
/*void writeFile(Node *head, const char *filename) {
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
}*/

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



void readBuffer(const char *bufferR, const char *buffer) {

    const char *delimiter = " \t\n"; // Delimitadores para palabras
    char *word = strtok(strdup(buffer), delimiter); // Duplicar buffer para evitar modificarlo
    while (word != NULL) {
        addWord(head, word);
        word = strtok(NULL, delimiter);
    }

    bufferR = saveToBuffer(head);
   
}


//-------------------Parte de verificacion de palabra concurrente--------------------------

// Función para agregar o actualizar una palabra en la lista general hacer la suma de los diferentes conteos
void addOrUpdateWord(Node **head, char *word, int count) {
    Node *current = *head;
    Node *previous = NULL;
    // Buscar si la palabra ya está en la lista
    while (current != NULL && strcmp(current->word, word) != 0) {
        //printf("Word: %s \n", word);
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        // Si la palabra no está en la lista, agregar un nuevo nodo
        Node *newNode = createNode(word);
        newNode->count = count;
        if (previous == NULL) {
            *head = newNode;
        } else {
            previous->next = newNode;
        }
    } else {

        // Si la palabra ya está en la lista, sumar el conteo
        current->count = current->count + count;
    }

}


// Función para leer palabras de un buffer y agregarlas a la lista
void mergedBuffer(Node **head, char *buffer) {
    char *line = strtok(buffer, "\n");
    while (line != NULL) {
        char word[256];
        int count;
        if (sscanf(line, "%255[^:]: %d", word, &count) == 2) {
            addOrUpdateWord(head, word, count);
        }
        line = strtok(NULL, "\n");
    }
}

// Función para encontrar la palabra más frecuente en la lista final
Node* findMostFrequentWord(Node *head) {
    Node *current = head;
    Node *mostFrequent = NULL;

    while (current != NULL) {
        if (mostFrequent == NULL || current->count > mostFrequent->count) {
            mostFrequent = current;
        }
        current = current->next;
    }

    return mostFrequent;
}


//--------------------------Funcion principal ------------------------------------------

int main(int argc, char *argv[]) {
    Node *head = NULL;

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

  

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

    if(rank==1){
        char mensajeCifrado[MAXIMA_LONGITUD_CADENA];
        char *buffer1;

        printf("Hola soy esclavo 1\n");

        readBuffer(buffer1,local_chunk);
        
        int local_lengths_1 = strlen(buffer1);

        //Cifra resultado que se envia al Manager 
        cifrar(buffer1, mensajeCifrado, 3);
        MPI_Send(&local_lengths_1, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        MPI_Send(mensajeCifrado, local_lengths_1, MPI_CHAR, 0,TAG, MPI_COMM_WORLD);
        free(buffer1);
        //freeList(head1);

    }else if(rank==2){

        char mensajeCifrado[MAXIMA_LONGITUD_CADENA];
        char *buffer2;

        char mensajeCifrado[MAXIMA_LONGITUD_CADENA], mensajeDescifrado[MAXIMA_LONGITUD_CADENA];
        Node *head2 = NULL;

        printf("Hola soy esclavo 2\n");
        readBuffer(buffer2,local_chunk);
        
        //char *buffer2 = saveToBuffer(head2);


        int local_lengths_2 = strlen(buffer2);
        

        //Cifra resultado que se envia al Manager 
        cifrar(buffer2, mensajeCifrado, 3);
        MPI_Send(&local_lengths_2, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        MPI_Send(mensajeCifrado, local_lengths_2, MPI_CHAR, 0,TAG, MPI_COMM_WORLD);



        free(buffer2);
        //freeList(head2);

        
    }else if(rank==3){

        char mensajeCifrado[MAXIMA_LONGITUD_CADENA];
        char *buffer3;
    
        //Node *head3 = NULL;
        printf("Hola soy esclavo 3\n");
        readBuffer(buffer3,local_chunk);

        //char *buffer3 = saveToBuffer(head3);


        int local_lengths_3 = strlen(buffer3);

        MPI_Send(&local_lengths_3, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        MPI_Send(buffer3, local_lengths_3, MPI_CHAR, 0,TAG, MPI_COMM_WORLD);

        free(buffer3);
        //freeList(head3);
        
    }
    else if(rank==4){
        char mensajeCifrado[MAXIMA_LONGITUD_CADENA];
        char *buffer4;

       
        printf("Hola soy esclavo 4\n");
        readBuffer(buffer4,local_chunk);

        //char *buffer4 = saveToBuffer(head4);
        int local_lengths_4 = strlen(buffer4);

        MPI_Send(&local_lengths_4, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        MPI_Send(buffer4, local_lengths_4, MPI_CHAR, 0,TAG, MPI_COMM_WORLD);

        free(buffer4);
       
        
    }
    else if(rank==5){
        char mensajeCifrado[MAXIMA_LONGITUD_CADENA];
        char *buffer5;


        printf("Hola soy esclavo 5\n");
        readBuffer(buffer5,local_chunk);

        //char *buffer5 = saveToBuffer(head5);
        int local_lengths_5 = strlen(buffer5);

        MPI_Send(&local_lengths_5, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        MPI_Send(buffer5, local_lengths_5, MPI_CHAR, 0,TAG, MPI_COMM_WORLD);

        free(buffer5);
        
        
    }
    else if(rank==6){

        char mensajeCifrado[MAXIMA_LONGITUD_CADENA];
        char *buffer6;
        printf("Hola soy esclavo 6\n");
        readBuffer(buffer6,local_chunk);

        //char *buffer6 = saveToBuffer(head6);


        int local_lengths_6 = strlen(buffer6);

        MPI_Send(&local_lengths_6, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        MPI_Send(buffer6, local_lengths_6, MPI_CHAR, 0,TAG, MPI_COMM_WORLD);

        free(buffer6);
      
        
    }
    else if(rank==7){

        char mensajeCifrado[MAXIMA_LONGITUD_CADENA];
        char *buffer7;

        //Node *head7 = NULL;
        printf("Hola soy esclavo 7\n");
        readBuffer(buffer7,local_chunk);

        //char *buffer7 = saveToBuffer(head7);


        int local_lengths_7 = strlen(buffer7);

        MPI_Send(&local_lengths_7, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        MPI_Send(buffer7, local_lengths_7, MPI_CHAR, 0,TAG, MPI_COMM_WORLD);

        free(buffer7);
        //freeList(head7);
        
    }


    if (rank==0){
        int local_lengths_1,local_lengths_2,local_lengths_3;
        int local_lengths_4,local_lengths_5,local_lengths_6,local_lengths_7;
        if (size==1)
        {
            /* code */
            printf("Hola soy master trabajando\n");
            char *buffer0;
            readBuffer(buffer0,local_chunk);
    
            //char *buffer0= saveToBuffer(head0);
            int local_lengths_0 = strlen(buffer0);
      
            //freeList(head0);
            buffer0[local_lengths_0] = '\0';
            printf("Tamaño_del_buffer_0:%d\n",local_lengths_0);
            printf("Chunk_del_buffer_0:%s\n",buffer0);
            free(buffer0);

        }else if (size==2){
            printf("Hola soy master trabajando\n");
    
            // Crear una nueva lista para almacenar los conteos combinados
            Node *mergedHead = NULL;
            char buffer_1_descifrado;
            char *buffer0;

            readBuffer(buffer0,local_chunk);
    
            //char *buffer0= saveToBuffer(head0);
            int local_lengths_0 = strlen(buffer0);
      
            //freeList(head0);
            buffer0[local_lengths_0] = '\0';
            printf("Tamaño_del_buffer_0:%d\n",local_lengths_0);
            printf("Chunk_del_buffer_0:%s\n",buffer0);
            mergedBuffer(&mergedHead, buffer0);
            

            MPI_Recv(&local_lengths_1,1,MPI_INT,1,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            char *buffer_1 = (char *)malloc(local_lengths_1 +1 );
            
            MPI_Recv(buffer_1, local_lengths_1, MPI_CHAR, 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            descifrar(buffer_1, buffer_1_descifrado, 3);
            buffer_1_descifrado;[local_lengths_1] = '\0';


            printf("Tamaño_de_buffer_1:%d\n",local_lengths_1);


            printf("Chunk_del_buffer_1:%s\n",buffer_1_descifrado);
            mergedBuffer(&mergedHead,buffer_1_descifrado);
            

            // Encontrar la palabra más frecuente
            Node *mostFrequent = findMostFrequentWord(mergedHead);
            // Mostrar e imprimir la palabra más frecuente
            if (mostFrequent != NULL) {
                printf("Most frequent word: %s (%d occurrences)\n", mostFrequent->word, mostFrequent->count);
            } else {
                printf("No words found in the list.\n");
            }

            free(buffer0);
            free(buffer_1_descifrado);
            freeList(mergedHead);

        }else if (size==3){
            printf("Hola soy master trabajando\n");
            char *buffer0;

            readBuffer(buffer0,local_chunk);
    
            //char *buffer0= saveToBuffer(head0);
            int local_lengths_0 = strlen(buffer0);
      
            freeList(head0);
            buffer0[local_lengths_0] = '\0';
            printf("Tamaño_del_buffer_0:%d\n",local_lengths_0);
            printf("Chunk_del_buffer_0:%s\n",buffer0);

            free(buffer0);

            MPI_Recv(&local_lengths_1,1,MPI_INT,1,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_2,1,MPI_INT,2,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
           
          

            char *buffer_1 = (char *)malloc(local_lengths_1 +1 );
            char *buffer_2 = (char *)malloc(local_lengths_2 +1);
            

            MPI_Recv(buffer_1, local_lengths_1, MPI_CHAR, 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_2, local_lengths_2, MPI_CHAR, 2, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            buffer_1[local_lengths_1] = '\0';
            buffer_2[local_lengths_2] = '\0';


            printf("Tamaño_de_buffer_1:%d\n",local_lengths_1);
            printf("Tamaño_de_buffer_2:%d\n",local_lengths_2);


            printf("Chunk_del_buffer_1:%s\n",buffer_1);
            printf("Chunk_del_buffer_2:%s\n",buffer_2);

            
            free(buffer_1);
            free(buffer_2);

        }else if (size==4){
            printf("Hola soy master trabajando\n");
            char *buffer0;

            readBuffer(buffer0,local_chunk);
            int local_lengths_0 = strlen(buffer0);
      
            freeList(head0);
            buffer0[local_lengths_0] = '\0';
            printf("Tamaño_del_buffer_0:%d\n",local_lengths_0);
            printf("Chunk_del_buffer_0:%s\n",buffer0);
            free(buffer0);

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

        }else if (size==5){
            printf("Hola soy master trabajando\n");
            char *buffer0;

            readBuffer(buffer0,local_chunk);
            int local_lengths_0 = strlen(buffer0);
      
            freeList(head0);
            buffer0[local_lengths_0] = '\0';
            printf("Tamaño_del_buffer_0:%d\n",local_lengths_0);
            printf("Chunk_del_buffer_0:%s\n",buffer0);
            free(buffer0);

            MPI_Recv(&local_lengths_1,1,MPI_INT,1,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_2,1,MPI_INT,2,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_3,1,MPI_INT,3,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_4,1,MPI_INT,4,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
          

            char *buffer_1 = (char *)malloc(local_lengths_1 +1 );
            char *buffer_2 = (char *)malloc(local_lengths_2 +1);
            char *buffer_3 = (char *)malloc(local_lengths_3 +1);
            char *buffer_4 = (char *)malloc(local_lengths_4 +1);
            

            MPI_Recv(buffer_1, local_lengths_1, MPI_CHAR, 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_2, local_lengths_2, MPI_CHAR, 2, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_3, local_lengths_3, MPI_CHAR, 3, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_4, local_lengths_3, MPI_CHAR, 4, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            buffer_1[local_lengths_1] = '\0';
            buffer_2[local_lengths_2] = '\0';
            buffer_3[local_lengths_3] = '\0';
            buffer_4[local_lengths_4] = '\0';


            printf("Tamaño_de_buffer_1:%d\n",local_lengths_1);
            printf("Tamaño_de_buffer_2:%d\n",local_lengths_2);
            printf("Tamaño_de_buffer_3:%d\n",local_lengths_3);
            printf("Tamaño_de_buffer_4:%d\n",local_lengths_4);


            printf("Chunk_del_buffer_1:%s\n",buffer_1);
            printf("Chunk_del_buffer_2:%s\n",buffer_2);
            printf("Chunk_del_buffer_3:%s\n",buffer_3);
            printf("Chunk_del_buffer_4:%s\n",buffer_4);

            
            free(buffer_1);
            free(buffer_2);
            free(buffer_3);
            free(buffer_4);

        }else if (size==6){
            printf("Hola soy master trabajando\n");
            char *buffer0;
            readBuffer(buffer0,local_chunk);
            int local_lengths_0 = strlen(buffer0);
      
            freeList(head0);
            buffer0[local_lengths_0] = '\0';
            printf("Tamaño_del_buffer_0:%d\n",local_lengths_0);
            printf("Chunk_del_buffer_0:%s\n",buffer0);
            free(buffer0);

            MPI_Recv(&local_lengths_1,1,MPI_INT,1,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_2,1,MPI_INT,2,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_3,1,MPI_INT,3,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_4,1,MPI_INT,4,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_5,1,MPI_INT,5,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
           

            char *buffer_1 = (char *)malloc(local_lengths_1 +1 );
            char *buffer_2 = (char *)malloc(local_lengths_2 +1);
            char *buffer_3 = (char *)malloc(local_lengths_3 +1);
            char *buffer_4 = (char *)malloc(local_lengths_4 +1);
            char *buffer_5 = (char *)malloc(local_lengths_5 +1);
           

            MPI_Recv(buffer_1, local_lengths_1, MPI_CHAR, 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_2, local_lengths_2, MPI_CHAR, 2, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_3, local_lengths_3, MPI_CHAR, 3, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_4, local_lengths_3, MPI_CHAR, 4, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_5, local_lengths_3, MPI_CHAR, 5, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);     
           

            buffer_1[local_lengths_1] = '\0';
            buffer_2[local_lengths_2] = '\0';
            buffer_3[local_lengths_3] = '\0';
            buffer_4[local_lengths_4] = '\0';
            buffer_5[local_lengths_5] = '\0';
            

            printf("Tamaño_de_buffer_1:%d\n",local_lengths_1);
            printf("Tamaño_de_buffer_2:%d\n",local_lengths_2);
            printf("Tamaño_de_buffer_3:%d\n",local_lengths_3);
            printf("Tamaño_de_buffer_4:%d\n",local_lengths_4);
            printf("Tamaño_de_buffer_5:%d\n",local_lengths_5);
          

            printf("Chunk_del_buffer_1:%s\n",buffer_1);
            printf("Chunk_del_buffer_2:%s\n",buffer_2);
            printf("Chunk_del_buffer_3:%s\n",buffer_3);
            printf("Chunk_del_buffer_4:%s\n",buffer_4);
            printf("Chunk_del_buffer_5:%s\n",buffer_5);
            
            free(buffer_1);
            free(buffer_2);
            free(buffer_3);
            free(buffer_4);
            free(buffer_5);


        }else if (size==7){
            printf("Hola soy master trabajando\n");
            char *buffer0;

            readBuffer(buffer0,local_chunk);
            int local_lengths_0 = strlen(buffer0);
      
            freeList(head0);
            buffer0[local_lengths_0] = '\0';
            printf("Tamaño_del_buffer_0:%d\n",local_lengths_0);
            printf("Chunk_del_buffer_0:%s\n",buffer0);
            free(buffer0);

            MPI_Recv(&local_lengths_1,1,MPI_INT,1,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_2,1,MPI_INT,2,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_3,1,MPI_INT,3,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_4,1,MPI_INT,4,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_5,1,MPI_INT,5,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_6,1,MPI_INT,6,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

            char *buffer_1 = (char *)malloc(local_lengths_1 +1 );
            char *buffer_2 = (char *)malloc(local_lengths_2 +1);
            char *buffer_3 = (char *)malloc(local_lengths_3 +1);
            char *buffer_4 = (char *)malloc(local_lengths_4 +1);
            char *buffer_5 = (char *)malloc(local_lengths_5 +1);
            char *buffer_6 = (char *)malloc(local_lengths_6 +1);

            MPI_Recv(buffer_1, local_lengths_1, MPI_CHAR, 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_2, local_lengths_2, MPI_CHAR, 2, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_3, local_lengths_3, MPI_CHAR, 3, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_4, local_lengths_3, MPI_CHAR, 4, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_5, local_lengths_3, MPI_CHAR, 5, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);     
            MPI_Recv(buffer_6, local_lengths_3, MPI_CHAR, 6, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            buffer_1[local_lengths_1] = '\0';
            buffer_2[local_lengths_2] = '\0';
            buffer_3[local_lengths_3] = '\0';
            buffer_4[local_lengths_4] = '\0';
            buffer_5[local_lengths_5] = '\0';
            buffer_6[local_lengths_6] = '\0';

            printf("Tamaño_de_buffer_1:%d\n",local_lengths_1);
            printf("Tamaño_de_buffer_2:%d\n",local_lengths_2);
            printf("Tamaño_de_buffer_3:%d\n",local_lengths_3);
            printf("Tamaño_de_buffer_4:%d\n",local_lengths_4);
            printf("Tamaño_de_buffer_5:%d\n",local_lengths_5);
            printf("Tamaño_de_buffer_6:%d\n",local_lengths_6);

            printf("Chunk_del_buffer_1:%s\n",buffer_1);
            printf("Chunk_del_buffer_2:%s\n",buffer_2);
            printf("Chunk_del_buffer_3:%s\n",buffer_3);
            printf("Chunk_del_buffer_4:%s\n",buffer_4);
            printf("Chunk_del_buffer_5:%s\n",buffer_5);
            printf("Chunk_del_buffer_6:%s\n",buffer_6);
            
            
            free(buffer_1);
            free(buffer_2);
            free(buffer_3);
            free(buffer_4);
            free(buffer_5);
            free(buffer_6);  
            
        }else if (size==8){  
            printf("Hola soy master trabajando\n");
            char *buffer0;

            readBuffer(buffer0,local_chunk);
            int local_lengths_0 = strlen(buffer0);
      
            freeList(head0);
            buffer0[local_lengths_0] = '\0';
            printf("Tamaño_del_buffer_0:%d\n",local_lengths_0);
            printf("Chunk_del_buffer_0:%s\n",buffer0);
            free(buffer0);  

            MPI_Recv(&local_lengths_1,1,MPI_INT,1,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_2,1,MPI_INT,2,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_3,1,MPI_INT,3,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_4,1,MPI_INT,4,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_5,1,MPI_INT,5,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_6,1,MPI_INT,6,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&local_lengths_7,1,MPI_INT,7,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

            char *buffer_1 = (char *)malloc(local_lengths_1 +1 );
            char *buffer_2 = (char *)malloc(local_lengths_2 +1);
            char *buffer_3 = (char *)malloc(local_lengths_3 +1);
            char *buffer_4 = (char *)malloc(local_lengths_4 +1);
            char *buffer_5 = (char *)malloc(local_lengths_5 +1);
            char *buffer_6 = (char *)malloc(local_lengths_6 +1);
            char *buffer_7 = (char *)malloc(local_lengths_7 +1);

            MPI_Recv(buffer_1, local_lengths_1, MPI_CHAR, 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_2, local_lengths_2, MPI_CHAR, 2, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_3, local_lengths_3, MPI_CHAR, 3, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_4, local_lengths_3, MPI_CHAR, 4, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_5, local_lengths_3, MPI_CHAR, 5, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);     
            MPI_Recv(buffer_6, local_lengths_3, MPI_CHAR, 6, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer_7, local_lengths_3, MPI_CHAR, 7, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            buffer_1[local_lengths_1] = '\0';
            buffer_2[local_lengths_2] = '\0';
            buffer_3[local_lengths_3] = '\0';
            buffer_4[local_lengths_4] = '\0';
            buffer_5[local_lengths_5] = '\0';
            buffer_6[local_lengths_6] = '\0';
            buffer_7[local_lengths_7] = '\0';

            printf("Tamaño_de_buffer_1:%d\n",local_lengths_1);
            printf("Tamaño_de_buffer_2:%d\n",local_lengths_2);
            printf("Tamaño_de_buffer_3:%d\n",local_lengths_3);
            printf("Tamaño_de_buffer_4:%d\n",local_lengths_4);
            printf("Tamaño_de_buffer_5:%d\n",local_lengths_5);
            printf("Tamaño_de_buffer_6:%d\n",local_lengths_6);
            printf("Tamaño_de_buffer_7:%d\n",local_lengths_7);

            printf("Chunk_del_buffer_1:%s\n",buffer_1);
            printf("Chunk_del_buffer_2:%s\n",buffer_2);
            printf("Chunk_del_buffer_3:%s\n",buffer_3);
            printf("Chunk_del_buffer_4:%s\n",buffer_4);
            printf("Chunk_del_buffer_5:%s\n",buffer_5);
            printf("Chunk_del_buffer_6:%s\n",buffer_6);
            printf("Chunk_del_buffer_7:%s\n",buffer_7);
            
            
            free(buffer_1);
            free(buffer_2);
            free(buffer_3);
            free(buffer_4);
            free(buffer_5);
            free(buffer_6);  
            free(buffer_7);
        }
        
        

    }

   
    free(buffer);
    free(local_chunk);
    MPI_Finalize();
    return 0;
}