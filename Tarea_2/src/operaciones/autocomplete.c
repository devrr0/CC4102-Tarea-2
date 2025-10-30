#include <stdio.h>
#include <stdlib.h>
#include "../estructuras/nodo.c"

/* Función que retorna un puntero al nodo terminal que representa el mejor autocompletado
    según el subárbol de 𝑣.
    @param v: Puntero al nodo del trie
*/ 
Nodo *autocomplete(Nodo *v);