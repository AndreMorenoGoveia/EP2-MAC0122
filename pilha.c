#include "pilha.h"



int max(int a, int b){

    if(a > b)
        return a;

    return b;

}



pilha* criaPilha(int tamanho, int x, int y){

    int i = 0;
    int maior = max(x, y);

    pilha* p = malloc(sizeof(pilha));

    p->v = malloc(tamanho*sizeof(item));

    for(i = 0; i < tamanho; i++){

        p->v[i].alter = malloc(maior*sizeof(int));
        p->v[i].lista = malloc(tamanho*sizeof(int));

    }


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