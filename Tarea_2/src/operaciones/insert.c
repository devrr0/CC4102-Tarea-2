#include <stdio.h>
#include <stdlib.h>
#include "../estructuras/nodo.c"
#include "crear_trie.c"

/* Funcion para insertar la palabra 𝑤 caracter por carácter.
    @param w: Caracter a insertar
*/ 
void insert(Trie *t, char *w){
    Nodo *actual = t->raiz;

    for(int i=0; i<strlen(w); i++){
        int index = char_index(w[i]);
        if(index==-1) return error(1);  // Caracter no valido

        if(!actual->next[index]){
            actual->next[index] = inicializar_nodo(actual);    
            t->num_nodos++;
        }
        actual = actual->next[index];
    }
    if(!actual->next[26]){
        Nodo *nodo_terminal = inicializar_nodo(actual);
        nodo_terminal->str = strdup(w);
        actual->next[27] = nodo_terminal;
        t->num_nodos++;
    }

}