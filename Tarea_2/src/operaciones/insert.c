#include <stdio.h>
#include <stdlib.h>

Nodo *inicializar_nodo(Nodo* parent);
void crear_nodo_terminal(Nodo *n, char *w);
void update_priority(Nodo *v);

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
            if(hijo->next[26] != NULL){
                Nodo *terminal = hijo->next[26];
                char *s = terminal->str;
                int j=i+1;
                while (j<strlen(w) && j<strlen(s) && w[j]==s[j]) j++;

                if (j==strlen(w) && j==strlen(s)){
                    update_priority(terminal);
                    return;
                }

                Nodo *nodo_diff = actual;
                for(int k=i; k<j; k++){   // comenzar crear nodos iguales
                    int index2 = char_index(w[k]);
                    nodo_diff->next[index2] = inicializar_nodo(nodo_diff);
                    t->num_nodos++;
                    nodo_diff = nodo_diff->next[index2];
                }
                // fin camino palabra w
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
                hijo->next[26] = NULL;
                return;
            }
        }
        actual = actual->next[index];
    }
    crear_nodo_terminal(actual, w);
    update_priority(actual->next[26]);
    t->num_nodos++;
}

