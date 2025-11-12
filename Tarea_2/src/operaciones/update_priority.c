#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static long long logical_counter = 0;

/* Función que actualiza la prioridad del nodo terminal 𝑣 según la variante y actualiza los
    nodos en el camino a la raíz.
    @param v: Puntero al nodo del trie
    @param variante: 1 si es prioridad por cantidad de accesos y 0 si es por tiempo de acceso
*/ 
void update_priority(Nodo *v, int variante){
    if(variante){       // cantidad de accesos
        // prioridad -> palabra con mayor frecuencia de accesos
        v->priority++;
    } else{             // tiempo de acceso
        // prioridad -> palabra que fue accedida de forma más reciente
        clock_t clk_time = clock();
        v->priority = (long long)clk_time + (++logical_counter);
    }
    v->best_terminal = v;
    v->best_priority = v->priority;
    Nodo *actual = v->parent;       // propagar hacia arriba actualizando padres
    while(actual != NULL){
        // verificar si este nodo terminal tiene mayor prioridad que el actual
        if(actual->best_terminal == NULL || v->priority > actual->best_priority){
        // Actualizar ya que no había best_terminal o tiene mayor prioridad
            actual->best_priority = v->priority;
            actual->best_terminal = v;
        }
        else if(actual->best_terminal == v){
            // si v era el best_terminal aumenta prioridad
            actual->best_priority = v->priority;
        }
        else break;      // no es necesario seguir propagando
        actual = actual->parent;
    }
}