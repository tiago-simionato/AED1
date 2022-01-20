#ifndef ARVORESTR_H
#define ARVORESTR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nostr{
	char *palavra;
	int tam;
	struct Nostr* esq;
	struct Nostr* dir;
} Nostr;

typedef struct Arvorestr{
	Nostr* raiz;
} Arvorestr;

void copiaValor (Nostr* original, char* s);

int str_compare (const char *stra, const char *strb);

Arvorestr* cria_arvorestr();

void inordemstr (Nostr* a);

void inserestr(Arvorestr *a, char *palavra);

int leafstr(Nostr* n);

int nodestr(Nostr* n);


#endif