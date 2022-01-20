#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct avlbt{
	int valor;
	struct avlbt* esq;
	struct avlbt* dir;
};

typedef struct avlbt no;

no* cria_no(int key);

void inordem (no* n); 

void preordem(no* n);

void posordem(no* n);

no* busca(no* root, int key);

no* insere(no* root, int key);

no* remover(no* root, int key);

int removefolha(no* root);

int altura(no* root);

int altmin(int n);

int altmin2(int n);

int nodes(no* n);

int leafs(no* n);

int pai(no* root, int key);

no* paiend(no* root, no* filho);

int fator_balanceamento(no* n);

no* rotacaoEsq(no* a);

no* rotacaoDir(no* a);

no* balanceador(no* n);

int max(int a, int b);

#endif