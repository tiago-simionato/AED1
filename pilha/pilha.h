#ifndef PILHA_H
#define PILHA_H

/****************************************************/
/*                                                  */
/*           PILHA DE INTEIROS POSITIVOS            */
/*                                                  */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>

/* Estrutura usada para representar um elemento da Pilha */
typedef struct No {
	int valor;               /*valor armazenado*/
	struct No* prox;         /*enereço do próximo elemento*/
} No;

/* Estrutura usada para representar o início da Fila */
typedef struct Fila {
	struct No* topo;       /* endereço no elemento no inicio da Pilha */
}Fila;


Pilha* cria_pilha();

int pilha_vazia(Pilha* P);

void empilha (Pilha* P, int n);

int desempilha (Pilha* P);

int topo (Pilha* P);

void imprime (Pilha* P);

#endif