#include <stdio.h>
#include <stdlib.h>

/* Dado un puntero a un nodo 𝑣 en el trie, retorna un puntero al nodo asociado a
    descender por el carácter 𝑐 o nulo en caso de no existir
    @param v: Puntero al nodo del trie
    @param c: Caracter por el cual descender
*/ 
Nodo *descend(Nodo *v, char c){
    if(v == NULL) return NULL;
    int index = char_index(c);
    if(index == -1) return NULL;
    return v->next[index];
}