#include <stdio.h>
#include <stdlib.h>
#include "../estructuras/nodo.c"

/* Función que actualiza la prioridad del nodo terminal 𝑣 según la variante y actualiza los
    nodos en el camino a la raíz.
    @param v: Puntero al nodo del trie
*/ 
void update_priority(Nodo *v);