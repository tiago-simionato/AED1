#include <stdio.h>
#include <stdlib.h>
#include "arvorestr.h"
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

void copiaValor (Nostr* original, char* s){

    char *c2 = malloc(strlen(s) * sizeof(char));

	int i;
	for(i=0; i<=strlen(s); i++) {
		c2[i]= s[i];
	}
	
	original->palavra = c2;
	original->tam = strlen(c2);
    
}

int str_compare (const char *stra, const char *strb){
    int i;
    if (strlen(stra) > strlen(strb)){
		return 1;
	}
	if (strlen(stra) < strlen(strb)){
		return -1;
	}
	for (i=0; i<= strlen(stra); i++) {
		if (stra[i]<strb[i]) {
			return -1;
		}
		if (stra[i]>strb[i]) {
			return 1;
		}
	}
	return 0;
}

Arvorestr* cria_arvorestr() {

	Arvorestr* novo = malloc(sizeof(Arvorestr));

	novo->raiz = NULL;

	return novo;
}

void inordemstr2(Nostr* n);

void inordemstr (Arvorestr* a) {
	inordemstr2(a->raiz);
	return;
}

void inordemstr2 (Nostr* n) {
	if (n != NULL) {
		inordemstr2(n->esq);
		int i;
		for(i=0; i< n->tam; i++) {
		printf("%c", n->palavra[i]);
		}
		printf("\n");
		inordemstr2(n->dir);
	}
	return;
}

void inserestr(Arvorestr *a, char *palavra) {
	Nostr *novo = malloc(sizeof(Nostr));
	novo->palavra = malloc( (strlen(palavra) + 1) *sizeof(char) );
	novo->esq = NULL;
	novo->dir = NULL;

	copiaValor(novo, palavra);

	if (a->raiz == NULL) {
		a->raiz = novo;
	}
	else {
		Nostr* atual = a->raiz;
		while(atual != NULL) {
			if(str_compare(novo->palavra, atual->palavra) == -1 ) {
				if (atual->esq == NULL) {
					atual->esq = novo;
					atual = NULL;
				} else{
					atual = atual->esq;
				}
			}
			else if(str_compare(novo->palavra, atual->palavra) >= 0 ) {
				if (atual->dir == NULL) {
					atual->dir = novo;
					atual = NULL;
				} else{
					atual = atual->dir;
				}
			}
		}
	}
	return;
}

int leafstr(Nostr* n) {
	if (n->esq == NULL && n->dir == NULL) {
		return 1;
	}
	if (n->esq != NULL && n->dir != NULL) {
		return leafstr(n->esq) + leafstr(n->dir);
	}
    if (n->esq == NULL) {
		return leafstr(n->dir);
	}
    if (n->dir == NULL) {
		return leafstr(n->esq);
	}
}


int nodestr(Nostr* n) {
    if (n->esq == NULL && n->dir == NULL) {
		return 1;
	}
    if (n->esq == NULL) {
		return nodestr(n->dir)+ 1;
	}
    if (n->dir == NULL) {
		return nodestr(n->esq) + 1;
	}
    return nodestr(n->esq) + nodestr(n->dir) + 1;
}

int main() {
	printf("qqq\n");
    Arvorestr* a = cria_arvorestr();
	char *p1 = malloc(sizeof(char)* 4);
	p1[0] = 'o';
	p1[1] = 'l';
	p1[2] = 'a';
	p1[3] = '\0';

    inserestr(a, p1);

	char *p2 = malloc(sizeof(char)* 4);
	p2[0] = 'a';
	p2[1] = 'b';
	p2[2] = 'c';
	p2[3] = '\0';
	inserestr(a, p2);

	printf("ateaqok\n");

	printf("%c\n", p1[0]);

	Nostr* teste = a->raiz;
	printf("%c\n", teste->palavra[0]);

	inserestr(a, "aquatro");
	inserestr(a, "a");
	inserestr(a, "zzz");

	inordemstr(a);
	printf("leaf: %d\n", leafstr(a->raiz));

    return 0;
}
