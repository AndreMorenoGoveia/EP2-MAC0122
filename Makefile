CC=gcc
CFlags=-Wall -ansi -pedantic -O2


all: ep2


ep2: ep2.o pilha.o
	$(CC) $(CFlags) ep2.o pilha.o


ep2.o: ep2.c
	$(CC) $(CFlags) -c ep2.c


pilha.o: pilha.c pilha.h
	$(CC) $(CFlags) -c pilha.c