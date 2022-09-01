#include "pilha.h"



pilha* criaPilha(int tamanho){

    pilha* p = malloc(sizeof(pilha));

    p->v = malloc(tamanho*sizeof(item));

    p->tam = 0;

    p->tamMax = tamanho;


}



void empilha(pilha* p, item i){

    if(p->tam < p->tamMax){

        p->v[p->tam] = i;
        p->tam++;

    }

}



item desempilha(pilha* p){

    p->tam--;
    return p->v[p->tam];
    
}



int pilhaVazia(pilha* p){

    return p->tam == 0;

}



void destroiPilha(pilha* p){

    free(p->v);
    free(p);

}