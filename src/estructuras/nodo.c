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
    struct Nodo **next[A];      
    int priority;       
    char *str;
    struct Nodo *best_terminal;
    int best_priority;
} Nodo;