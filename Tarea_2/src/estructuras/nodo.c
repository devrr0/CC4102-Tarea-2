#include <stdio.h>
#include <stdlib.h>
#define A 27

/* Estructura nodo arbol
    @param parent: Referencia a su nodo padre (nulo si el nodo es la raíz)
    @param next: Estructura que mapea caracteres del alfabeto a hijos
    @param priority: Cantidad de accesos a este nodo terminal
    @param str: Si el nodo es terminal esto debe contener un puntero al string asociado
    @param best_terminal: Puntero al nodo terminal del subárbol con mayor prioridad
    @param best_priority: Prioridad del nodo con mayor prioridad del subárbol
*/
typedef struct Nodo {
    struct Nodo *parent;  
    struct Nodo *next[A];      
    long long priority;       
    char *str;
    struct Nodo *best_terminal;
    long long best_priority;
} Nodo;

/* Estructura trie
    @param raiz: Referencia al nodo raiz
    @param num_nodos: Numero de nodos que esta usando la estructura
*/
typedef struct {
    Nodo* raiz;
    int num_nodos;  
    int variante;
} Trie;

/* Funcion para convertir caracter a indice
    @param c: Caracter a convertir
*/
int char_index(char c) {
    if (c == '$') return 26;  
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A';  
    return -1;  
}

/* Funcion para convertit indice a caracter
    @param indice: Indice a convertir
*/
char index_char(int indice) {
    if (indice == 26) return '$';
    if (indice >= 0 && indice < 26) return 'a' + indice;
    return '?';  
}