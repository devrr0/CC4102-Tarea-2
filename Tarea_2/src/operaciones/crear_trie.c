#include <stdio.h>
#include <stdlib.h>
#define A 27

/* Inicializar nodo
    @param parent: Referencia la nodo padre

    @return Nodo inicializado con valores 0
*/
Nodo *inicializar_nodo(Nodo* parent){
    Nodo *n = malloc(sizeof(Nodo)); 
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

/* Funcion para crear un nodo terminal
    @param n: Nodo padre
    @param w: Palabra correspondiente al nodo terminal
*/
void crear_nodo_terminal(Nodo *n, char *w){
    Nodo *nodo_terminal = inicializar_nodo(n);
    nodo_terminal->str = strdup(w);
    n->next[26] = nodo_terminal;
}

/* Inicializar trie
    @return Trie inicializado con nodo raiz
*/
Trie *inicializar_trie(int variante){
    Trie *t = malloc(sizeof(Trie));
    t->raiz = inicializar_nodo(NULL);
    t->num_nodos = 1;
    t->variante = variante;
    return t;
}

/* Libera la memoria de un nodo
    @param n: Nodo a liberar
*/
void liberar_nodo(Nodo *n) {
    for (int i = 0; i < A; i++) {
        if (n->next[i] != NULL) liberar_nodo(n->next[i]);
    }
    if (n->str) free(n->str);
    free(n);
}

/* Libera la memoria de un trie
    @param t: Trie a liberar
*/
void liberar_trie(Trie *t) {
    liberar_nodo(t->raiz);
    free(t);
}