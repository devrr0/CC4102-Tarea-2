#include <stdio.h>
#include <stdlib.h>

Nodo *inicializar_nodo(Nodo* parent);
void update_priority(Nodo *v);

/* Funcion para insertar la palabra 𝑤 caracter por carácter.
    @param w: Caracter a insertar
*/ 
void insert(Trie *t, char *w){
    Nodo *actual = t->raiz;
    
    // recorremos la palabra
    for(int i = 0; i < strlen(w); i++){
        int index = char_index(w[i]);
        if(index == -1) return;
        // Si no existe el hijo lo creamos
        if(actual->next[index] == NULL){
            actual->next[index] = inicializar_nodo(actual);
            t->num_nodos++;
        }

        actual = actual->next[index];
    }
    
    // agregar nodo terminal
    if(actual->next[26] == NULL){
        // primera vez que insertamos esta palabra
        actual->next[26] = inicializar_nodo(actual);
        actual->next[26]->str = strdup(w);
        t->num_nodos++;
    }
    
    // actualizar prioridad del nodo terminal
    update_priority(actual->next[26]);
}