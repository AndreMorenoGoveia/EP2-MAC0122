/***************************************************************/
/**                                                           **/
/**   André Moreno Goveia            NUSP 13682785            **/
/**   Exercício-Programa 02                                   **/
/**   Professor: Carlos Eduardo Ferreira                      **/
/**   Turma: 01                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

#define BUFFER_SIZE 4096


/* Estrutura de uma palavra */ 
typedef struct {

    char* word;
    int len;

} palavra;



/* Função responsável por encaixar uma palavra no tabuleiro, retorna 0
   caso não seja possível o encaixe e 1 caso contrário. A função altera
   as matrizes fornecidas.  */
int fit(palavra p, char** c_tab, int** tab, int x, int y);



/* Função responsável por imprimir a matriz com as palavras encaixadas */
void printtab(char** c_tab, int x, int y);



int main(void){

    int i, j;


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
    



    int b = 1;
    int* lista_proibida = (int*) calloc(l, sizeof(int));



    while(b){

        for(i = 0; i < l; i++){
            if(!lista_proibida[i]){
                if(fit(palavras[i], c_tab, tabuleiro, x, y)){
                    empilha(decisao); // fazer essa função
                    lista_proibida[i] = 1;
                }
                else
                    lista_proibida[i] = 1;
            }
        }

        if(taCerto()) // fazer essa função
            printtab(c_tab, x ,y);

        else{
            b = backtrack(); // fazer essa função
        }
            

    }







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




int fit(palavra p, char** c_tab, int** tab, int x, int y){

    int i, j, k;

    int l = 0;

    int h, jh;

    /* Busca horizontal */
    for(i = 0; i < x && l != p.len; i++){

        l = 0;

        for(j = 0; j < y && l != p.len; j++){
            
            if(tab[i][j] != -1)
                l++;
            else if(tab[i][j] == -2 && p.word[l-1] == c_tab[i][j])
                l++;
            else
                l = 0;

        }

    }
    h = l == p.len;
    jh = j - 1;

    /* Busca vertical */
    for(j = 0; j < y && l != p.len; j++){

        l = 0;

        for(i = 0; i < x && l != p.len; i++){
            
            if(tab[i][j] != -1)
                l++;
            else if(tab[i][j] == -2 && p.word[l-1] == c_tab[i][j])
                l++;
            else
                l = 0;

        }

    }


    if(l == p.len){

        if(h){
            i--;
            for(k = l - 1; k >= 0; k--){
                c_tab[i][jh] = p.word[k];
                tab[i][jh] = -2;
                jh--;
            }
        }

        else{
            i--;
            j--;
            for(k = l - 1; k >= 0; k--){
                c_tab[i][j] = p.word[k];
                tab[i][j] = -2;
                i--;
            }
        }
    }

    else 
        l = 0;



    return l != 0;

}

 

void printtab(char** c_tab, int x, int y){

    int i, j;
    
    for(i = 0; i < x; i++){
        printf("\n");
        for(j = 0; j < y; j++)
            printf("%c ", c_tab[i][j]);
    }

}


int backtrack(){

    

}