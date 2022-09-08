/***************************************************************/
/**                                                           **/
/**   André Moreno Goveia            NUSP 13682785            **/
/**   Exercício-Programa 02                                   **/
/**   Professor: Carlos Eduardo Ferreira                      **/
/**   Turma: 01                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include "pilha.h"

#define BUFFER_SIZE 4096



/* Função responsável por encaixar uma palavra no tabuleiro, retorna 0
   caso não seja possível o encaixe e 1 caso contrário. A função altera
   as matrizes fornecidas.  */
int encaixa();



/* Função responsável por imprimir a matriz com as palavras encaixadas */
void print_tab(char** c_tab, int x, int y);



/* Função que confere se todos os espaços em branco estão preenchidos */
int estaCerto(int** tab, int x, int y);



/* Função que checa se todas as palavras da lista foram testada */
int lotou(int* lista, int l);



/* Função que faz o backtrack desempilhando itens e ajeitando para a volta das
   listas de maneira adequada à função */
int backtrack();





int main(void){


    int i, j, cont = 0;



    /* Leitura dos tabuleiros */
    int x, y;
    scanf("%d %d", &x, &y);

    int** tabuleiro = (int**) malloc(x*sizeof(int*));
    for(i = 0; i < x; i++)
        *(tabuleiro + i) = (int*) malloc(y*sizeof(int));

    for(i = 0; i < x; i++)
        for(j = 0; j < y; j++)
            scanf("%d", *(tabuleiro + i) + j);
   




    /* Leitura das palavras */
    int l;
    scanf("%d", &l);
    palavra* palavras = (palavra*) malloc(l*sizeof(palavra));

    palavra* p;
    char buffer[BUFFER_SIZE];

    for(i = 0; i < l; i++){

        p = (palavras + i);
        p->len = 0;

        scanf("%s", buffer);

        for(j = 0; *(buffer + j) != '\0'; j++)
            p->len++;
        
        p->word = malloc(p->len*sizeof(char));

        for(j = 0; *(buffer + j) != '\0'; j++)
            p->word[j] = buffer[j];
        p->word[p->len] = '\0';

    }





    /* Inicia a matriz que armazenará as combinações */
    char** c_tab = (char**) malloc(x*sizeof(char*));
        for(i = 0; i < x; i++)
        *(c_tab + i) = (char*) malloc(y*sizeof(char));
    
    for(i = 0; i < x; i++)
        for(j = 0; j < y; j++)
            c_tab[i][j] = '*';
    



    cont = backtrack();

   



    if(cont == 0)
        printf("Nao ha solucao");
    





    /* Liberação da memória alocada */
    for(i = 0; i < x; i++)
        free(*(tabuleiro + i));
    free(tabuleiro);

    for(i = 0; i < l; i++)
        free((palavras + i)->word);
    free(palavras);

    for(i = 0; i < x; i++)
        free(*(c_tab + i));
    free(c_tab);





    return 0;
}



 



void print_tab(char** c_tab, int x, int y){

    int i, j;
    
    for(i = 0; i < x; i++){
        printf("\n");
        for(j = 0; j < y; j++)
            printf("%c ", c_tab[i][j]);
    }

}





int estaCerto(int** tab, int x, int y){

    int i, j;

    for(i = 0; i < x; i++)
        for(j = 0; j < y; j++)
            if(!tab[i][j])
                return 0;

    return 1;

}



