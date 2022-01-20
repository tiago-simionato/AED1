#ifndef FILA_H
#define FILA_H

/****************************************************/
/*                                                  */
/*           FiLA DE INTEIROS POSITIVOS             */
/*                                                  */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>

/* Estrutura usada para representar um elemento da Fila */
typedef struct No {
	int valor;               /*valor armazenado*/
	struct No* prox;         /*enereço do próximo elemento*/
} No;

/* Estrutura usada para representar o início da Fila */
typedef struct Fila {
	struct No* inicio;       /* endereço no elemento no inicio da fila */
}Fila;


Fila* cria_fila();

int fila_vazia(Fila* F);

void enfileira (Fila* F, int n);

int desenfileira (Fila* F);

int inicio_fila (Fila* F);

void imprime (Fila* F);

#endif