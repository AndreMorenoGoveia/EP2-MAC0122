#include "pilha.h"



pilha* criaPilha(int tam){

    pilha* p = malloc(sizeof(pilha));

    p->v = malloc(tam*sizeof(item));

    p->topo = -1;

    return p;


}



void empilha(pilha* p, item i){

    p->v[p->topo + 1] = i;
    p->topo++;

}



item desempilha(pilha* p){

    p->topo--;
    return p->v[p->topo + 1];

}



int pilhaVazia(pilha* p){

    return p->topo == -1;

}



void destroiPilha(pilha* p){

    (p->topo)++;
    while (p->topo--){

        free(p->v[p->topo].alter);
        free(p->v[p->topo].bloq);

    }

    free(p->v);
    free(p);

}
