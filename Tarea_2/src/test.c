#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras/nodo.c"
#include "operaciones/insert.c"
#include "operaciones/crear_trie.c"
#include "operaciones/update_priority.c"
#include "operaciones/autocomplete.c"
#define A 27

/* Funcion para imprimir un trie recursivamente
    @param nodo: Nodo actual
    @param nivel: Nivel del nodo en el trie
*/
void imprimir_trie_rec(Nodo *nodo, int nivel, FILE *file) { 
    for (int i=0; i<A; i++) {
        if (nodo->next[i]) {
            Nodo *actual = nodo->next[i];
            fprintf(file, "Nodo: %c ; Nivel: %d ; Prioridad: %d\n", index_char(i), nivel + 1, actual->priority);
            if (actual->str) {
                fprintf(file, "Palabra: %s\n", actual->str);
            }
            imprimir_trie_rec(actual, nivel+1, file);
        }
    }
}

/* Funcion para imprimir un trie
    @param trie: Trie a imprimir
*/
void imprimir_trie(Trie* trie, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error al abrir el archivo de salida: %s\n", filename);
        return;
    }
    // Imprimir trie
    fprintf(file, "=== Contenido del Trie ===\n");
    imprimir_trie_rec(trie->raiz, 0, file);
    fprintf(file, "==========================\n");
    // Imprimir autocompletado
    Nodo *raiz = trie->raiz;
    fprintf(file, "Autocompletar raiz: %s\n", autocomplete(raiz)->str);
    //fprintf(file, "Autocompletar h: %s\n", autocomplete(raiz->next['h' - 'a'])->str);

    fclose(file);
}


void main(){
    Trie* trie = inicializar_trie();
    FILE* archivo = fopen("../datos/words_sample.txt", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }
    char linea[256];
    int contador = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n\r")] = '\0';

        if (strlen(linea) > 0) {
            printf("Insertando linea: %s\n", linea);
            insert(trie, linea);  
            contador++;
        }
    }
    fclose(archivo);
    printf("Imprimiendo trie");
    imprimir_trie(trie, "../resultados/test.txt");
    liberar_trie(trie);
}