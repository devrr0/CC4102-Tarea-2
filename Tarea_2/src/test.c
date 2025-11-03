#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras/nodo.c"
#include "operaciones/insert.c"
#include "operaciones/crear_trie.c"
#define A 27

// Función auxiliar para imprimir el trie (para debugging)
void imprimir_trie_rec(Nodo *nodo, int nivel) { 

    for (int i=0; i<A; i++) {
        if (nodo->next[i]) {
            Nodo *actual = nodo->next[i];
            printf("Nodo: %c ; Nivel: %d\n", index_char(i), nivel + 1);
            if (actual->str) {
                printf("Palabra: %s\n", actual->str);
            }
            imprimir_trie_rec(actual, nivel + 1);
        }
    }
}

void imprimir_trie(Trie* trie) {
    if (!trie) return;
    char buffer[100];
    printf("=== Contenido del Trie ===\n");
    imprimir_trie_rec(trie->raiz, 0);
    printf("==========================\n");
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
            insert(trie, linea);  
            contador++;
        }
    }
    fclose(archivo);
    imprimir_trie(trie);
    liberar_trie(trie);
}