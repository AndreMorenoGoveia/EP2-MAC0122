#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096


/* Estrutura de uma palavra */ 
typedef struct {

    char* word;
    int len;

} palavra;






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
        p->len = 1;

        scanf("%s", buffer);

        for(j = 0; *(buffer + j) != '\0'; j++)
            p->len++;
        
        p->word = malloc(p->len*sizeof(char));

        for(j = 0; *(buffer + j) != '\0'; j++)
            p->word[j] = buffer[j];
        p->word[p->len - 1] = '\0';

    }









    /* Liberacao da memória alocada */
    for(i = 0; i < x; i++)
        free(*(tabuleiro + i));
    free(tabuleiro);

    for(i = 0; i < l; i++)
        free((palavras + i)->word);
    free(palavras);


    return 0;
}