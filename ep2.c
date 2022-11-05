/***************************************************************/
/**                                                           **/
/**   André Moreno Goveia            NUSP 13682785            **/
/**   Exercício-Programa 02                                   **/
/**   Professor: Carlos Eduardo Ferreira                      **/
/**   Turma: 01                                               **/
/**                                                           **/
/***************************************************************/

#include "pilha.h"
#include <stdio.h>


#define BUFFER_SIZE 4096



/* Função que printa o tabuleiro */
void print_tab(int** tab, int x, int y);



/* Função que encontra a solução para a entrada dada, encaixando palavras nos
   espaços vazios utilizando um backtrack com pilha para alterar as posições */
int encontra_solucao(int** tab , int x, int y, palavra* words, int p_cont);



/* Função que armazena as posições dos espaços vazios disponíveis */
espaco_vazio* encontra_espacos_vazios(int** tab, int x, int y, int* cont);



/* Função que tenta encaixar uma palavra selecionada em um espaço vazio selecionado
   caso consiga, a alteração no tablueiro e a posição do backtrack são empilhados */
void encaixa_palavra(palavra* words, int p_cont, espaco_vazio* evs, int* index,
                        pilha* p, int* bloq, int** tab);



/* Função que desempilha a última alteração e altera a posição do backtrack de acordo */
void desfaz(int** tab, pilha* p, int* index, int* bloq, int p_cont);





int main(void){

    int x, y;
    int i, j;
    int cont = 1;
    int p_cont;
    int len;
    int** tab;
    char buffer[BUFFER_SIZE];
    palavra* words;



    scanf("%d %d", &y, &x);

    while(x + y != 0){


        /* Leitura das entradas */
        tab = (int**) malloc(y*sizeof(int*));
        for(i = 0; i < y; i++)
            tab[i] = (int*) malloc(x*sizeof(int));


        for(i = 0; i < y; i++)
            for(j = 0; j < x; j++)
                scanf("%d", &tab[i][j]);


        scanf("%d", &p_cont);

        words = (palavra*) malloc(p_cont*sizeof(palavra));

        for(i = 0; i < p_cont; i++){

            scanf("%s", buffer);

            for(len = 1; buffer[len - 1] != '\0'; len++);

            words[i].len = len - 1;

            words[i].word = (char*) malloc(len*sizeof(char));

            while(len--)
                words[i].word[len] = buffer[len];

        }



        printf("Instancia %d:\n\n", cont);

        if(encontra_solucao(tab, x, y, words, p_cont))
            print_tab(tab, x, y);
        else
            printf("Nao ha solucao\n\n");

        cont++;



        for(i = 0; i < y; i++)
            free(tab[i]);
        free(tab);



        scanf("%d %d", &y, &x);

    }



        return 0;

}



int encontra_solucao(int** tab, int x, int y, palavra* words, int p_cont){

    int i, j;
    int cont = 0;

    int* bloq = (int*) calloc(p_cont, sizeof(int));

    espaco_vazio* evs = encontra_espacos_vazios(tab, x, y, &cont);

    pilha* p = criaPilha(cont);


    /* Backtrack para encontro de solução alterando a ordem
       das palavras em relação aos espacos vazios */
    for(i = 0; i < p_cont; i++){



        /* Empilha caso a palavra seja valida */
        encaixa_palavra(words, p_cont, evs, &i, p, bloq, tab);



        /* A pilha estará cheia caso todos os espaços vazios estiverem cheios
           e, portanto, foi encontrada solução */
        if(p->topo == cont - 1){
            free(evs);
            destroiPilha(p);
            return 1;
        }



        /* Desempilha e muda a ordem das palavras caso não tenha encontrado solução */
        if(i == p_cont - 1)
            desfaz(tab, p, &i, bloq, p_cont);

    }



    free(evs);
    destroiPilha(p);
    return 0;

}



espaco_vazio* encontra_espacos_vazios(int** tab, int x, int y, int* cont){

    int i, j, k;
    int len;
    espaco_vazio* evs;



    /* Contador horizontal */
    for(i = 0; i < y; i++){

        len = 0;

        for(j = 0; j < x; j++){

            if(tab[i][j] == 0)
                len++;
            else if(len > 1){
                (*cont)++;
                len = 0;
            }
            else len = 0;


        }

        if(len > 1)
            (*cont)++;

    }



    /* Contador vertical */
    for(j = 0; j < x; j++){

        len = 0;

        for(i = 0; i < y; i++){

            if(tab[i][j] == 0)
                len++;
            else if(len > 1){
                (*cont)++;
                len = 0;
            }
            else len = 0;


        }

        if(len > 1)
            (*cont)++;

    }



    evs = (espaco_vazio*) malloc((*cont) * sizeof(espaco_vazio));
    k = *cont - 1;

    /* Configuracao horizontal */
    for(i = 0; i < y; i++){

        len = 0;

        for(j = 0; j < x; j++){

            if(tab[i][j] == 0)
                len++;
            else if(len > 1){

                evs[k].len = len;
                evs[k].p.h = 1;
                evs[k].p.i = i;
                evs[k].p.j = j - len;
                
                k--;
                len = 0;
            }
            else len = 0;


        }

        if(len > 1){

            evs[k].len = len;
            evs[k].p.h = 1;
            evs[k].p.i = i;
            evs[k].p.j = j - len;

            k--;
        }

    }



    /* Configuracao vertical */
    for(j = 0; j < x; j++){

        len = 0;

        for(i = 0; i < y; i++){

            if(tab[i][j] == 0)
                len++;
            else if(len > 1){

                evs[k].len = len;
                evs[k].p.h = 0;
                evs[k].p.i = i - len;
                evs[k].p.j = j;
                
                k--;
                len = 0;
            }
            else len = 0;


        }

        if(len > 1){

            evs[k].len = len;
            evs[k].p.h = 0;
            evs[k].p.i = i - len;
            evs[k].p.j = j;

            k--;
        }

    }



    return evs;

}



void encaixa_palavra(palavra* words, int p_cont, espaco_vazio* evs, int* index,
                        pilha* p, int* bloq, int** tab){

    int i;

    if(bloq[(*index)])
        return;

    espaco_vazio ev = evs[p->topo + 1];



    /* Confere se a palavra cabe no espaco vazio */
    if(words[(*index)].len == ev.len){

        int* alter = calloc(ev.len, sizeof(int));



        /* Confere se a palavra nao colide com outras */
        /* Horizontal */
        if(ev.p.h){

            for(i = 0; i < ev.len; i++){

                if(tab[ev.p.i][i + ev.p.j] != 0){

                    if(tab[ev.p.i][i + ev.p.j] != words[(*index)].word[i]){
                        free(alter);
                        return;
                    }
                    else
                        alter[i] = 1;

                }

            }

        }



        /* Vertical */
        else{

            for(i = 0; i < ev.len; i++){

                if(tab[i + ev.p.i][ev.p.j] != 0){

                    if(tab[ev.p.i][i + ev.p.j] != words[(*index)].word[i]){
                        free(alter);
                        return;
                    }
                    else
                        alter[i] = 1;

                }

            }

        }



        /* Empilhando a alteração e a posição do backtrack */
        int* p_bloq = (int*) malloc(p_cont*sizeof(int));
        for(i = 0; i < p_cont; i++)
            p_bloq[i] = bloq[i];

        bloq[(*index)] = 1;


        item it;
        it.alter = alter;
        it.bloq = p_bloq;
        it.index = *index;
        it.len = ev.len;
        it.p = ev.p;

        empilha(p, it);

        /* Altera o tabuleiro */
        /* Horizontal */
        if(ev.p.h){

            for(i = 0; i < ev.len; i++)
                tab[ev.p.i][ev.p.j + i] = words[(*index)].word[i];

        }
        /* Vertical */
        else{

            for(i = 0; i < ev.len; i++)
                tab[ev.p.i + i][ev.p.j] = words[(*index)].word[i];
        

        }

        *index = -1;

    }
    else return;

}


void desfaz(int** tab, pilha* p, int* index, int* bloq, int p_cont){

    int i;



    /* Caso tenha chego no limite do backtrack o código encerra */
    if(pilhaVazia(p))
        return;



    item it = desempilha(p);

    for(i = 0; i < p_cont; i++)
        bloq[i] = it.bloq[i];

    
    /* Desfazendo alteracoes */
    /* Horizontal */
    if(it.p.h){

        for(i = 0; i < it.len; i++){

            if(!it.alter[i])
                tab[it.p.i][it.p.j + i] = 0;

        }

    }
    /* Vertical */
    else{

        for(i = 0; i < it.len; i++){

            if(!it.alter[i])
                tab[it.p.i + i][it.p.j] = 0;

        }

    }



    /* Preparando para a proxima analise no backtrack */
    if(it.index < p_cont - 1)
        *index = it.index;
    else
        desfaz(tab, p, index, bloq, p_cont);

    free(it.alter);
    free(it.bloq);

}



void print_tab(int** tab, int x, int y){

    int i, j;

    for(i = 0; i < y; i++){

        for(j = 0; j < x; j++){

            if(tab[i][j] == -1)
                tab[i][j] = '*';

            printf("%c ", (char) tab[i][j]);

        }

        printf("\n");

    }

    printf("\n");

}
