#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include "estructuras/nodo.c"
#include "operaciones/insert.c"
#include "operaciones/crear_trie.c"
#include "operaciones/update_priority.c"
#include "operaciones/autocomplete.c"
#include "operaciones/descend.c"
#define A 27
#define M 16

/* Funcion auxiliar para realizar analisis de autocompletado en un texto
    @param file_in: Archivo de texto con palabras a buscar
    @param file_out: Archivo de texto para guardar resultados
    @param trie: Trie sobre el cual hacer autocompletado
*/
void analisis_autocomplete(FILE *file_in, FILE *file_out, Trie *trie){
    int total_chars = 0;
    int chars_w = 0;
    int cnt_words = 0;
    int nxt_pow = 1;
    int exp = 0;
    clock_t start = clock();

    char linea[256];
    int cnt = 0;
    char c;
    while ((c = fgetc(file_in)) != EOF){
        if (isspace(c)) {
            if (cnt == 0) continue;  
            linea[cnt] = '\0';
            cnt = 0;
            cnt_words++;
            total_chars += strlen(linea);

            Nodo *actual = trie->raiz;
            int word_in = 0;
            int user_w = 0;
            for(int i=0; i<strlen(linea); i++){
                actual = descend(actual, linea[i]);
                user_w++;
                if(actual == NULL){
                    chars_w += strlen(linea);
                    break;
                }
                Nodo *autoc = autocomplete(actual);
                if(autoc && autoc->str && strcmp(autoc->str, linea) == 0){
                    chars_w += user_w;
                    word_in = 1;
                    update_priority(autoc);
                    break;
                }
                if(i == strlen(linea)-1){
                    chars_w += strlen(linea);
                    break;
                }
            }
            if(word_in) update_priority(actual->best_terminal);
            if(cnt_words == nxt_pow){
                double porc = (total_chars > 0 ? 100*((double)chars_w / total_chars) : 0);
                printf("En N = 2^%d\n", exp); 
                fprintf(file_out, "------ Para N = 2^%d ------\n", exp);
                fprintf(file_out, "%.5f %% caracteres escritos\n", porc);
                exp++;
                nxt_pow <<= 1;
            }
            continue;
        }
        if (cnt < 255) linea[cnt++] = c;
    }
    clock_t end = clock();
    double total_time = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(file_out, "------ Tiempos de la estructura ------\n");
    fprintf(file_out, "Tiempo total: %.6f s\n", total_time);
    fprintf(file_out, "Tiempo normalizado (por palabra): %.10f s/pal\n", total_time / cnt_words);
    fprintf(file_out, "Tiempo normalizado (por caracter): %.10f s/char\n", total_time / total_chars);
}

/* Funcion auxiliar para aplicar analisis de autocompletado 
    @param filename: Nombre del archivo de texto con palabras a buscar
    @param file_out: Archivo de texto para guardar resultados
    @param trie: Trie sobre el cual hacer autocompletado
*/
void experimento2(const char* filename, FILE *archivo_out, Trie *trie){
    FILE* archivo = fopen(filename, "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }
    Trie *trie_aux = trie;
    printf("En archivo %s\n", filename);
    fprintf(archivo_out, "---------- Para archivo %s ----------\n", filename);
    analisis_autocomplete(archivo, archivo_out, trie_aux);
    fclose(archivo);
}

/* Funcion auxiliar para los experimentos
    @param archivo_out: Archivo de texto para guardar resultados
    @param archivo_out_time: Archivo de texto para guardar resultados de tiempo
*/
void experimento(FILE *archivo_out, FILE *archivo_out_time){
    Trie* trie = inicializar_trie();
    FILE* archivo_in = fopen("../datos/words.txt", "rb");
    if (archivo_in == NULL) {
        printf("Error al abrir el archivo\n");
        liberar_trie(trie);
        return;
    }
    fprintf(archivo_out, "---------- INSERTANDO WORDS.TXT ----------\n");
    printf("---------- INSERTANDO WORDS.TXT ----------\n");
    int nxt_pow = 1;
    int exp = 0;
    int N = 1<<18;
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
                double nodos_norm = cnt_insert > 0 ? (double)nodos/(double)cnt_insert : 0.0;
                printf("En N = 2^%d\n", exp); 
                fprintf(archivo_out, "------ Para N = 2^%d ------\n", exp);
                fprintf(archivo_out, "Cantidad de nodos : %d\n", nodos);
                fprintf(archivo_out, "Cantidad de nodos normalizado : %.6f\n", nodos_norm);
                exp++;
                nxt_pow <<= 1;
            }
            if(cnt % size_group == 0){
                clock_t end = clock();
                double time = (double)(end - start) / CLOCKS_PER_SEC;
                double time_norm = (cnt_chars > 0 ? time / cnt_chars : 0.0);
                fprintf(archivo_out_time, "Grupo %d ; Tiempo: %.10f ; Tiempo normalizado: %.10f\n", actual_group, time, time_norm);
                actual_group++;
                cnt_chars=0;
                start = clock();
            }
        }
    }
    fclose(archivo_in);
    printf("---------- INSERCION TERMINADA ----------\n");
    printf("---------- COMENZANDO ANALISIS DE AUTOCOMPLETADO ----------\n");
    fprintf(archivo_out, "---------- ANALISIS AUTOCOMPLETADO ----------\n");
    experimento2("../datos/wikipedia.txt", archivo_out, trie);
    experimento2("../datos/random.txt", archivo_out, trie);
    experimento2("../datos/random_with_distribution.txt", archivo_out, trie);
    printf("---------- ANALISIS DE AUTOCOMPLETADO TERMINADO ----------\n");
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
    printf("\n---------- EJECUTANDO EXPERIMENTO ----------\n");
    experimento(file1, file2);
    fclose(file1);
    fclose(file2);
}