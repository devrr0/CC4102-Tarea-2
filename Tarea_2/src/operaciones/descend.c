#include <stdio.h>
#include <stdlib.h>
#include "../estructuras/nodo.c"

/*  Funcion auxiliar que convierte un carácter en un índice del arreglo de hijos
    @param c: Caracter a convertir
    @return: Índice correspondiente en el arreglo de hijos
*/
int char_to_index(char c) {
    if (c == '$') { // fin de la palabra
        return 26;
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    return -1; // no es valido
}

/* Dado un puntero a un nodo 𝑣 en el trie, retorna un puntero al nodo asociado a
    descender por el carácter 𝑐 o nulo en caso de no existir
    @param v: Puntero al nodo del trie
    @param c: Caracter por el cual descender
*/ 
Nodo *descend(Nodo *v, char *c){
    if (v == NULL || c == NULL) {
        return NULL;
    }
    int indice = char_to_index(*c);
    if (indice == -1) {
        return NULL; // no es valido
    }
    return v->children[indice];
}
