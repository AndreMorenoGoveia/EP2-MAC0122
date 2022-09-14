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




/* Função responsável por imprimir a matriz com as palavras encaixadas */
void print_tab(char** c_tab, int x, int y);






int main(void){


    int i, j;



    /* Leitura dos tabuleiros */
    int x, y;
    scanf("%d %d", &x, &y);

    int** tab = (int**) malloc(x*sizeof(int*));
    for(i = 0; i < x; i++)
        *(tab + i) = (int*) malloc(y*sizeof(int));

    for(i = 0; i < x; i++)
        for(j = 0; j < y; j++)
            scanf("%d", *(tab + i) + j);





    /* Leitura das palavras */
    int l;
    scanf("%d", &l);
    palavras words = (palavras) malloc(l*sizeof(palavra));

    palavra* temp;
    char buffer[BUFFER_SIZE];

    for(i = 0; i < l; i++){

        temp = (words + i);
        temp->len = 0;

        scanf("%s", buffer);

        for(j = 0; *(buffer + j) != '\0'; j++)
            temp->len++;

        temp->word = malloc(temp->len*sizeof(char));

        for(j = 0; *(buffer + j) != '\0'; j++)
            temp->word[j] = buffer[j];
        temp->word[temp->len] = '\0';

    }





    /* Inicia a matriz que armazenará as combinações */
    char** c_tab = (char**) malloc(x*sizeof(char*));
        for(i = 0; i < x; i++)
        *(c_tab + i) = (char*) malloc(y*sizeof(char));

    for(i = 0; i < x; i++)
        for(j = 0; j < y; j++)
            c_tab[i][j] = '*';




    pilha* p = criaPilha(l, x, y);


    int* repetidos = (int*) calloc(l, sizeof(int));



    /* Encontra primeiro espaco vago e inicia a busca */
    int len = 0;
    for(i = 0; i < x; i++){
        for(j = 0; j < y; j++){

            if(!tab[i][j])
                len++;
            else if(len == 1)
                encontra(tab, c_tab, x, y, 0, repetidos, l, len, words, p, i - len + 1 , j);
            else if(len > 1)
                encontra(tab, c_tab, x, y, 1, repetidos, l, len, words, p, i, j - len + 1);
            else
                len = 0;

        }
    }


    if(estaCerto(tab, x, y))
        print_tab(c_tab, x, y);

    else
        printf("Nao ha solucao\n");



    /* Liberação da memória alocada */
    for(i = 0; i < x; i++)
        free(*(tab + i));
    free(tab);

    for(i = 0; i < l; i++)
        free((words + i)->word);
    free(words);

    for(i = 0; i < x; i++)
        free(*(c_tab + i));
    free(c_tab);

    destroiPilha(p, l);



    return 0;
}




void encontra(int** tab, char** c_tab, int x, int y, int h, int* repetidas,
                 int l, int len, palavras words, pilha* p, int i0, int j0){

        int i, j, k;
        item it = { encontraPalavra(words, len, repetidas, l), i0, j0, len };
        palavra w = words[it.index];

        if(h){

            if(it.index >= 0){

                for(j = 0; j < len; j++){

                    c_tab[i0][j0 + j] = w.word[j];
                    tab[i0][j0 + j] -= 2;
                    it.alter[j0 + j] = 2;

                }

                empilha(p, it);

            }

            else if(pilhaVazia(p)) {}

            else{

                it = desempilha(p);
                repetidas[it.index] = 0;
                encontra(tab, c_tab, x, y, 0, repetidas, l, it.len, words, p, it.i, it.j);

            }


        }

        else{

            if(it.index >= 0){

                for(i = 0; i < len; i++){

                    c_tab[i0 + i][j0] = w.word[i];
                    tab[i0 + i][j0] -= 2;
                    it.alter[i0 + i] = 2;

                }

                empilha(p, it);
            }

            else if(pilhaVazia(p)) return 0;

            else{

                it = desempilha(p);
                repetidas[it.index] = 0;

            }

        }

    return 1;


}



int encontraPalavra(palavra* words, int len, int* repetidas, int l){

    int i;

    for(i = 0; i < l; i++){

        if(!repetidas[i] && len == words[i].len){

            repetidas[i] = 1;
            return i;

        }

    }

    return -1;

}



int estaCerto(int** tab, int x, int y){

    int i, j;

    for(i = 0; i < x; i++)
        for(j = 0; j < y; j++)
            if(!tab[i][j])
                return 0;

    return 1;

}






void print_tab(char** c_tab, int x, int y){

    int i, j;

    for(i = 0; i < x; i++){
        printf("\n");
        for(j = 0; j < y; j++)
            printf("%c ", c_tab[i][j]);
    }

}
