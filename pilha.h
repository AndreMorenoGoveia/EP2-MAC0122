/* Estrutura de uma palavra */ 
typedef struct {

    char* word;
    int len;

} palavra;



/* Estrutura dos itens da pilha */
typedef struct {
    
    int* alter;
    int i;
    int j;

} item;



/* Estrutura da pilha */
typedef struct{
    
    item* v;
    int tam;
    int tamMax;

} pilha;


/* Aloca memória para uma pilha e seus itens */
pilha* criaPilha(int tamanho);



/* Adiciona os valores de um item ao topo da pilha */
void empilha(pilha* p, item i);



/* Remove o item do topo da pilha e o retorna */
item desempilha(pilha* p);



/* Retorna 1 caso a pilha esteja vazia e 0 caso contrário */
int pilhaVazia(pilha* p);



/* Libera a memória alocada pela pilha */
void destroiPilha(pilha* p)