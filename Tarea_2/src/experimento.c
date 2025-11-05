#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "estructuras/nodo.c"
#include "operaciones/insert.c"
#include "operaciones/crear_trie.c"
#include "operaciones/update_priority.c"
#include "operaciones/autocomplete.c"
#define A 27
#define M 16
#define N 1<<18

void experimento1(FILE *archivo_out, FILE *archivo_out_time){
    Trie* trie = inicializar_trie();
    FILE* archivo_in = fopen("../datos/words.txt", "rb");
    if (archivo_in == NULL) {
        printf("Error al abrir el archivo\n");
        liberar_trie(trie);
        return;
    }
    fprintf(archivo_out, "---------- INSERTANDO WORDS.TXT ----------\n");
    fprintf(archivo_out_time, "---------- INSERTANDO WORDS.TXT ----------\n");
    int nxt_pow = 1;
    int exp = 0;
    int size_group = N/M;
    int actual_group = 1;
    int cnt_chars = 0;
    int cnt_insert = 0;
    clock_t start = clock();

    char linea[256];
    int cnt = 0;
    while (fgets(linea, sizeof(linea), archivo_in)) {
        linea[strcspn(linea, "\n\r")] = '\0';
        
        if (strlen(linea) > 0) {
            cnt_chars+=strlen(linea);
            cnt_insert+=strlen(linea);
            insert(trie, linea);  
            cnt++;
            if(cnt==nxt_pow){
                int nodos = trie->num_nodos;
                int nodos_norm = (cnt_insert > 0 ? nodos / cnt_insert : 0);
                fprintf(archivo_out, "------ Para N = 2^%d ------\n", exp);
                fprintf(archivo_out, "Cantidad de nodos : %d\n", nodos);
                fprintf(archivo_out, "Cantidad de nodos normalizado : %d\n", nodos_norm);
                exp++;
                nxt_pow <<= 1;
            }
            if(cnt % size_group == 0){
                clock_t end = clock();
                double time = (double)(end - start) / CLOCKS_PER_SEC;
                double time_norm = (cnt_chars > 0 ? time / cnt_chars : 0.0);
                fprintf(archivo_out_time, "Grupo %d ; Tiempo normalizado: %.10f\n", actual_group, time_norm);
                actual_group++;
                cnt_chars=0;
                start = clock();
            }
        }
    }
    fclose(archivo_in);
    liberar_trie(trie);
}

void main(){
    FILE *file1 = fopen("../resultados/experimento.txt", "w");
    if (!file1) {
        printf("Error al abrir el archivo de salida\n");
        return;
    }
    FILE *file2 = fopen("../resultados/experimento_tiempo.txt", "w");
    if (!file2) {
        printf("Error al abrir el archivo de salida\n");
        return;
    }
    printf("\n---------- EJECUTANDO EXPERIMENTO 1 ----------\n");
    experimento1(file1, file2);
    fclose(file1);
    fclose(file2);
}