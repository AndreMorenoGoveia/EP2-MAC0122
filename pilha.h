#include <stdlib.h>

/* Estrutura de uma palavra */ 
typedef struct {

    char* word;
    int len;

} palavra;



/* Estrutura da posição de um espaço vazio */
typedef struct{

    int i;
    int j;
    int h;

}pos;



/* Estrutura de um espaço vazio */
typedef struct {

    int len;
    pos p;

} espaco_vazio;



/* Estrutura dos itens da pilha */
typedef struct {

    int* alter;
    int* bloq;

    pos p;
    int len;

    int index;

} item;



/* Estrutura da pilha */
typedef struct{

    item* v;
    int topo;

} pilha;



/* Aloca memória para uma pilha e seus itens de acordo com o tamanho fornecido */
pilha* criaPilha(int tam);



/* Adiciona um item ao topo da pilha */
void empilha(pilha* p, item i);



/* Remove o item do topo da pilha e o retorna */
item desempilha(pilha* p);



/* Retorna 1 caso a pilha esteja vazia e 0 caso contrário */
int pilhaVazia(pilha* p);



/* Libera a memória alocada pela pilha */
void destroiPilha(pilha* p);
