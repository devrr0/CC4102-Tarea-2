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
    int variante = trie->variante;
    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Error al abrir el archivo de salida: %s\n", filename);
        return;
    }
    // Imprimir trie
    if(variante) fprintf(file, "=== Variante cantidad de accesos ===\n");
    else fprintf(file, "=== Variante tiempo de accesos ===\n");
    fprintf(file, "=== Contenido del Trie ===\n");
    imprimir_trie_rec(trie->raiz, 0, file);
    fprintf(file, "==========================\n");
    fprintf(file, "=== Autocompletado raiz del Trie ===\n");
    fprintf(file, "Autocompletar raiz: %s\n", autocomplete(trie->raiz)->str);
    fprintf(file, "==========================\n");
    fclose(file);
}


void main(){
    Trie* trie_v1 = inicializar_trie(1);
    Trie* trie_v2 = inicializar_trie(0);
    FILE* archivo = fopen("../datos/words_sample.txt", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }
    char linea[256];
    int contador = 0;
    printf("Comenzando insercion\n");
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n\r")] = '\0';

        if (strlen(linea) > 0) {
            insert(trie_v1, linea);  
            insert(trie_v2, linea);  
            contador++;
        }
    }
    fclose(archivo);
    printf("Imprimiendo trie\n");
    imprimir_trie(trie_v1, "../resultados/test.txt");
    imprimir_trie(trie_v2, "../resultados/test.txt");
    liberar_trie(trie_v1);
    liberar_trie(trie_v2);
}