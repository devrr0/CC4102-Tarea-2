#include <stdio.h>
#include <stdlib.h>
#include "../estructuras/nodo.c"
#define A 27

/* Inicializar nodo
    @param parent: Referencia la nodo padre

    @return Nodo inicializado con valores 0
*/
Nodo *inicializar_nodo(Nodo* parent){
    Nodo* n = malloc(sizeof(Nodo)); 
    n->parent = parent;
    for (int i = 0; i < A; i++) {
        n->next[i] = NULL;
    }
    n->priority = 0;
    n->str = NULL;
    n->best_terminal = NULL;
    n->best_priority = 0;

    return n;
}

void *crear_nodo_terminal(Nodo *n, char *w){
    Nodo *nodo_terminal = inicializar_nodo(n);
    nodo_terminal->str = strdup(w);
    n->next[26] = nodo_terminal;
}

/* Inicializar trie
    @return Trie inicializado con nodo raiz
*/
Trie *inicializar_trie(){
    Trie* t = malloc(sizeof(Trie));
    t->raiz = inicializar_nodo(NULL);
    t->num_nodos = 1;
    
    return t;
}

/* Libera la memoria de un trie
    @param t: Trie a liberar
*/
void liberar_trie(Trie *t);