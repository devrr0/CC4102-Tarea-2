#include <stdio.h>
#include <stdlib.h>

/* Función que actualiza la prioridad del nodo terminal 𝑣 según la variante y actualiza los
    nodos en el camino a la raíz.
    @param v: Puntero al nodo del trie
*/ 
void update_priority(Nodo *v){
    v->priority++;
    Nodo *actual = v->parent;
    while(actual!=NULL){
        if(v->priority > actual->best_priority){
            actual->best_priority = v->priority;
            actual->best_terminal = v;
        }
        actual=actual->parent;
    }
}