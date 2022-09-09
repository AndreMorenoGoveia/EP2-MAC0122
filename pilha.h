#include <stdlib.h>

/* Estrutura de uma palavra */ 
typedef struct {

    char* word;
    int len;

} palavra;



/* Estrutura dos itens da pilha */
typedef struct {

    int* char_alter;
    int i;
    int j;
    int index;

    int* restricted;

} item;



/* Estrutura da pilha */
typedef struct{

    item* v;
    int tam;

} pilha;



/* Função que calcula o maior número entre dois inteiros */
int max(int a, int b);



/* Aloca memória para uma pilha e seus itens */
pilha* criaPilha(int l, int x, int y);



/* Adiciona os valores de um item ao topo da pilha */
void empilha(pilha* p, item i);



/* Remove o item do topo da pilha e o retorna */
item desempilha(pilha* p);



/* Retorna 1 caso a pilha esteja vazia e 0 caso contrário */
int pilhaVazia(pilha* p);



/* Libera a memória alocada pela pilha */
void destroiPilha(pilha* p, int l);