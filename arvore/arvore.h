#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct No{
	int valor;
	struct No* esq;
	struct No* dir;
} No;

typedef struct {
	No* raiz;
} Arvore;

Arvore* cria_arvore();

void inordem (No* a); 

void preordem(No* a);

void posordem(No* a);

No* busca(No* n, int v);

void insere(Arvore* a, int elemento);

void remover(Arvore* a, int elemento);

int altura(No* n);

int altmin(int n);

int nodes(No* n);

int leafs(No* n);

int pai(Arvore* a, int chave);

#endif