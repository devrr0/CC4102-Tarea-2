#include <stdio.h>
#include <stdlib.h>
// #include "../estructuras/nodo.c"

Nodo *inicializar_nodo(Nodo* parent);
void crear_nodo_terminal(Nodo *n, char *w);

/* Funcion para insertar la palabra 𝑤 caracter por carácter.
    @param w: Caracter a insertar
*/ 
void insert(Trie *t, char *w){
    Nodo *actual = t->raiz;

    for(int i=0; i<strlen(w); i++){
        int index = char_index(w[i]);
        if(index==-1) return;      // Caracter no valido
        Nodo *hijo = actual->next[index];

        if(hijo == NULL){
            actual->next[index] = inicializar_nodo(actual);    
            t->num_nodos++;
            crear_nodo_terminal(actual->next[index], w);
            t->num_nodos++;
            return;
        }
        else{
            if(hijo->next[26] != NULL){
                Nodo *terminal = hijo->next[26];
                char *s = terminal->str;
                int j=i+1;
                while (j<strlen(w) && j<strlen(s) && w[j]==s[j]) j++;

                if (j==strlen(w) && j==strlen(s)) return;

                Nodo *nodo_diff = actual;
                for(int k=i; k<j; k++){   // comenzar crear nodos iguales
                    int index2 = char_index(w[k]);
                    nodo_diff->next[index2] = inicializar_nodo(nodo_diff);
                    t->num_nodos++;
                    nodo_diff = nodo_diff->next[index2];
                }
                int index_w = char_index(w[j]);
                int index_s = char_index(s[j]);
                nodo_diff->next[index_w] = inicializar_nodo(nodo_diff);
                crear_nodo_terminal(nodo_diff->next[index_w], w);
                nodo_diff->next[index_s] = inicializar_nodo(nodo_diff);
                crear_nodo_terminal(nodo_diff->next[index_s], s);
                t->num_nodos+=4;
                hijo->next[26] = NULL;
                return;
            }
        }
        actual = actual->next[index];
    }
    crear_nodo_terminal(actual, w);
    t->num_nodos++;
}

