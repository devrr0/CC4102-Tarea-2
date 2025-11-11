#include <stdio.h>
#include <stdlib.h>

Nodo *inicializar_nodo(Nodo* parent);
void crear_nodo_terminal(Nodo *n, char *w);
void update_priority(Nodo *v);

void crear_camino_prefijo(Nodo *nodo, char *c1, char *c2, int index){
    crear_nodo_terminal(nodo, c1);
    update_priority(nodo->next[26]);
    int nxt_index = char_index(c2[index]);
    nodo->next[nxt_index] = inicializar_nodo(nodo);    
    crear_nodo_terminal(nodo->next[nxt_index], c2);
    update_priority(nodo->next[nxt_index]->next[26]);
}

/* Funcion para insertar la palabra 𝑤 caracter por carácter.
    @param w: Caracter a insertar
*/ 
void insert(Trie *t, char *w){
    Nodo *actual = t->raiz;

    for(int i=0; i<strlen(w); i++){
        int index = char_index(w[i]);
        if(index==-1) return;      // Caracter no valido
        Nodo *hijo = actual->next[index];

        if(hijo == NULL){
            actual->next[index] = inicializar_nodo(actual);    
            t->num_nodos++;
            crear_nodo_terminal(actual->next[index], w);
            update_priority(actual->next[index]->next[26]);
            t->num_nodos++;
            return;
        }
        else{
            if(i<strlen(w) && hijo->next[w[i+1]] == NULL){     // si el siguiente indice esta vacio (para que vaya a hijo==NULL)
                if(hijo->next[26] != NULL && strcmp(w, hijo->next[26]->str)==0) return;
                actual = actual->next[index];                   // seguir recorriendo el trie
                continue;
            }
            if(hijo->next[26] != NULL){
                Nodo *terminal = hijo->next[26];
                char *s = terminal->str;
                int j=i;
                while (j<strlen(w) && j<strlen(s) && w[j]==s[j]) j++;

                if (j==strlen(w) && j==strlen(s)){
                    update_priority(terminal);
                    return;
                }    
                Nodo *nodo_diff = actual;
                for(int k=i; k<j; k++){   // comenzar crear nodos iguales
                    int index2 = char_index(w[k]);
                    if(nodo_diff->next[index2] == NULL){        // si es que el nodo no existe -> lo creo
                        nodo_diff->next[index2] = inicializar_nodo(nodo_diff);
                        t->num_nodos++;
                    } 
                    nodo_diff = nodo_diff->next[index2];
                }
                if(j==strlen(s) && j<strlen(w)){        // si s es prefijo de w
                    hijo->next[26] = NULL;              // eliminar nodo terminal previo
                    crear_camino_prefijo(nodo_diff, s, w, j);
                    t->num_nodos+=3; 
                    return;
                } 
                if(j==strlen(w) && j<strlen(s)){        // si w es prefijo de s
                    hijo->next[26] = NULL;              // eliminar nodo terminal previo
                    crear_camino_prefijo(nodo_diff, w, s, j);
                    t->num_nodos+=3; 
                    return;
                }
                // fin camino palabra w
                hijo->next[26] = NULL;              // eliminar nodo terminal previo
                int index_w = char_index(w[j]);
                nodo_diff->next[index_w] = inicializar_nodo(nodo_diff);
                crear_nodo_terminal(nodo_diff->next[index_w], w);
                update_priority(nodo_diff->next[index_w]->next[26]);
                // fin camino palabra s
                int index_s = char_index(s[j]);
                nodo_diff->next[index_s] = inicializar_nodo(nodo_diff);
                crear_nodo_terminal(nodo_diff->next[index_s], s);
                update_priority(nodo_diff->next[index_s]->next[26]);
                t->num_nodos+=4; 
                return;
            }
            else{
                crear_nodo_terminal(hijo, w);
                update_priority(hijo->next[26]);
                t->num_nodos++;
                return;
            }
        }
        actual = actual->next[index];
    }
    if (actual->next[26] != NULL) {
        update_priority(actual->next[26]);
        return;
    }
    crear_nodo_terminal(actual, w);
    update_priority(actual->next[26]);
    t->num_nodos++;
}
