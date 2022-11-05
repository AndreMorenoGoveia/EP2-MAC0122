# EP2-MAC0122

Exercício-Programa 2 cujo objetivo era fazer um programa que preenchesse corretamente um caça
palavras, de acordo com os espaços disponíveis e as palavras disponíveis possíveis.


# Backtrack

Para resolver o exercício foi utilizado um backtrack iterativo com pilha que ia alternando a ordem
das palavras em relação aos espaços vazios até encontrar uma solução.


# Exemplo

Para a entrada:

5 4

-1  0  0  0\
 0  0  0  0\
 0  0 -1  0\
 0  0  0  0\
 0 -1  0  0\
10\
ad\
antas\
carn\
casa\
do\
lado\
lua\
os\
soda\
0 0\

O programa deve retornar

Instancia 1\
\* l u a\
c a r n\
a d * t\
s o d a\
a * o s\
