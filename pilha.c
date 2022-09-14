#include "pilha.h"



int max(int a, int b){

    if(a > b)
        return a;

    return b;

}



pilha* criaPilha(int l, int x, int y){

    int i = 0;
    int maior = max(x, y);

    pilha* p = malloc(sizeof(pilha));

    p->v = malloc(l*sizeof(item));

    for(i = 0; i < l; i++){

        p->v[i].alter = calloc(maior, sizeof(int));

    }


    p->tam = 0;

    return p;


}



void empilha(pilha* p, item i){

    p->v[p->tam] = i;
    p->tam++;

}



item desempilha(pilha* p){

    p->tam--;
    return p->v[p->tam];

}



int pilhaVazia(pilha* p){

    return p->tam == 0;

}



void destroiPilha(pilha* p, int l){

    int i;

    for(i = 0; i < p->tam; i++)
        free(p->v[i].alter);

    free(p->v);
    free(p);

}