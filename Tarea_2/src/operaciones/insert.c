#include <stdio.h>
#include <stdlib.h>

Nodo *inicializar_nodo(Nodo* parent);
void crear_nodo_terminal(Nodo *n, char *w);
void update_priority(Nodo *v, int variante);

/* Funcion para insertar la palabra 𝑤 caracter por carácter.
    @param t: Trie con contador de nodos
    @param w: Caracter a insertar
*/ 
void insert(Trie *t, char *w){
    int variante = t->variante;
    Nodo *actual = t->raiz;

    for(int i=0; i<strlen(w); i++){
        int index = char_index(w[i]);
        if(index==-1) return;      // Caracter no valido

        if(actual->next[index] == NULL){
            actual->next[index] = inicializar_nodo(actual);    
            t->num_nodos++;
        }
        actual = actual->next[index];
    }
    if (actual->next[26] != NULL) {
        update_priority(actual->next[26], variante);
        return;
    }
    crear_nodo_terminal(actual, w);
    update_priority(actual->next[26], variante);
    t->num_nodos++;
}
