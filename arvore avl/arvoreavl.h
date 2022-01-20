#ifndef ARVOREAVL_H
#define ARVOREAVL_H

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

void inordem (No* n); 

void preordem(No* n);

void posordem(No* n);

No* busca(No* n, int v);

void insere(Arvore* a, int elemento);

void remover(Arvore* a, int elemento);

int removefolha(No* n);

int altura(No* n);

int altmin(int n);

int altmin2(int n);

int nodes(No* n);

int leafs(No* n);

int pai(Arvore* a, int chave);

No* paiend(No* raiz, No* filho);

int fator_balanceamento(No* n);

int desbalanceado(No* n);

void rotacaoesq(Arvore* a, No* atual);

void rotacaodir(Arvore* a, No* atual);

void balanceador(Arvore* a, No*atual);

#endif