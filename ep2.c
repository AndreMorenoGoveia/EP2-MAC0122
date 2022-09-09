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
int encaixa(char** c_tab, int** tab, int x, int y, pilha* pil, palavra p, int* lista, int l, int index);



/* Função responsável por remover as alterações da tabela ao desempilhar um item da pilha */
item desencaixa(int** tab, char** c_tab, int x, int y, int* lista, int l, pilha* p);



/* Função responsável por imprimir a matriz com as palavras encaixadas */
void print_tab(char** c_tab, int x, int y);



/* Função que confere se todos os espaços em branco estão preenchidos */
int estaCerto(int** tab, int x, int y);



/* Função que testa se há permutações possíveis na atual camada da pilha */
int lotado(int* lista, int index, int l);



/* Função que faz o backtrack empilhando e desempilhando itens e assim passando por
   todas as permutações possíveis  */
int backtrack(pilha* p, palavra* words, int l, char** c_tab, int** tab, int x, int y);





int main(void){


    int i, j, cont = 0;



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
    palavra* palavras = (palavra*) malloc(l*sizeof(palavra));

    palavra* temp;
    char buffer[BUFFER_SIZE];

    for(i = 0; i < l; i++){

        temp = (palavras + i);
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




    cont = backtrack(p, palavras, l, c_tab, tab, x, y);





    if(cont == 0)
        printf("Nao ha solucao");






    /* Liberação da memória alocada */
    for(i = 0; i < x; i++)
        free(*(tab + i));
    free(tab);

    for(i = 0; i < l; i++)
        free((palavras + i)->word);
    free(palavras);

    for(i = 0; i < x; i++)
        free(*(c_tab + i));
    free(c_tab);

    destroiPilha(p, l);



    return 0;
}



 int lotado(int* lista, int index, int l){

    if(index >= l)
        return 1;

    int i;
    for(i = index; i < l; i++)
        if(!lista[i])
            return 1;

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






int encaixa(char** c_tab, int** tab, int x, int y, pilha* pil, palavra p, int* lista, int l, int index){


    int i, j = 0, k;
    int le = 0;
    int h, jh;

    item a;



    /* Busca horizontal */
    for(i = 0; i < x && le != p.len; i++){

        le = 0;

        for(j = 0; j < y && le != p.len; j++){

            if(tab[i][j] == 0)
                le++;
            else if(tab[i][j] <= -2 && p.word[le] == c_tab[i][j])
                le++;
            else
                le = 0;

        }

    }
    h = le == p.len;
    jh = j - 1;



    /* Busca vertical */
    for(j = 0; j < y && le != p.len; j++){

        le = 0;

        for(i = 0; i < x && le != p.len; i++){

            if(tab[i][j] == 0)
                le++;
            else if(tab[i][j] <= -2 && p.word[le] == c_tab[i][j])
                le++;
            else
                le = 0;

        }

    }



    if(le == p.len){

        if(h){

            a.char_alter = (int*) calloc(x, sizeof(int));
            i--;
            a.i = i;
            a.j = -1;
            for(k = le - 1; k >= 0; k--){
                c_tab[i][jh] = p.word[k];
                tab[i][jh] += -2;
                a.char_alter[jh] = 2;
                jh--;
            }
        }

        else{

            a.char_alter = (int*) calloc(y, sizeof(int));
            i--;
            j--;
            a.j = j;
            for(k = le - 1; k >= 0; k--){
                c_tab[i][j] = p.word[k];
                tab[i][j] += -2;
                a.char_alter[i] = 2;
                i--;
            }
        }



        lista[index] = 1;
        a.restricted = (int*) malloc(l*sizeof(int));

        for(i = 0; i < l; i++)
            a.restricted[i] = lista[i];

        a.index = index;

        empilha(pil, a);

    }


    free(a.char_alter);
    free(a.restricted);


}




item desencaixa(int** tab, char** c_tab, int x, int y, int* lista, int l, pilha* p){

    int i, j;

    item a = desempilha(p);

    a.restricted[a.index] = 0;

    /* Horizontal */
    if(a.j == -1){

        for(j = 0; j < y; j++){

            tab[a.i][j] += a.char_alter[j];
            if(tab[a.i][j] == 0)
                c_tab[a.i][j] = '*';


        }


    }
    /* Vertical */
    else{

        for(i = 0; i < y; i++){

            tab[i][a.j] += a.char_alter[i];
            if(!(tab[i][a.j]))
                c_tab[i][a.j] = '*';


        }

    }


}



int backtrack(pilha* p, palavra* words, int l, char** c_tab, int** tab, int x, int y){

    int i, j, k, cont = 0;
    item a;
    int pindex = 0;
    int b = 1;
    int* lista = (int*) calloc(l, sizeof(int));

    while(1){

        for(i = pindex; i < l; i++){
            if(!lista[i]){
                
                encaixa(c_tab, tab, x, y, p,
                        words[i], lista, l , i);
                i = 0;

            }
        }



        if(estaCerto(tab, x, y)){
            print_tab(c_tab, x, y);
            cont++;
        }



        do{


        if(pilhaVazia(p)){
            
            free(lista);
            return cont;

        }


        a = desencaixa(tab, c_tab, x, y, lista, l, p);
        pindex = a.index + 1;

        } while(lotado(lista, pindex, l));
        
        
        


    }

}