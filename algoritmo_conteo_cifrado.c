#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

// Función para agregar una palabra a la lista con un conteo específico
void addWord(Node **head, char *word) {
    Node *current = *head;
    Node *previous = NULL;

    // Convertir a minúsculas para evitar duplicados por mayúsculas
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

// Función para leer palabras de un archivo y almacenarlas en la lista
void readFile(Node **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char word[256];
    while (fscanf(file, "%255s", word) != EOF) {
        addWord(head, word);
    }

    fclose(file);
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

// Función para imprimir la lista de palabras y sus conteos
void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s: %d\n", current->word, current->count);
        current = current->next;
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


int main() {
    char mensajeCifrado[MAXIMA_LONGITUD_CADENA], mensajeDescifrado[MAXIMA_LONGITUD_CADENA];
    Node *head = NULL;

    // Leer las palabras del archivo de entrada
    readFile(&head, "C:\\Users\\Rachel\\CLionProjects\\prueba\\ca.txt");
    //printList(head);

    char *buffer1 = saveToBuffer(head);
    cifrar(buffer1, mensajeCifrado, 3);
    char *buffer2 = saveToBuffer(head);
    char *buffer3 = saveToBuffer(head);

    // Crear una nueva lista para almacenar los conteos combinados
    Node *mergedHead = NULL;
    descifrar(mensajeCifrado, mensajeDescifrado, 3);
    // Leer las palabras de los buffers y combinarlas en mergedHead
    mergedBuffer(&mergedHead, mensajeDescifrado);

    mergedBuffer(&mergedHead, buffer2);

    mergedBuffer(&mergedHead, buffer3);




    // Encontrar la palabra más frecuente
    Node *mostFrequent = findMostFrequentWord(mergedHead);

    // Mostrar e imprimir la palabra más frecuente
    if (mostFrequent != NULL) {
        printf("Most frequent word: %s (%d occurrences)\n", mostFrequent->word, mostFrequent->count);
    } else {
        printf("No words found in the list.\n");
    }


    free(buffer1);
    free(buffer2);
    free(buffer3);


    // Liberar la memoria
    freeList(head);
    freeList(mergedHead);

    return 0;
}