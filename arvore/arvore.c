#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include <string.h>

int main() {
	Arvore* a = cria_arvore();

	insere(a, 3);
	inordem(a);
	return 0;
}

/* Cria uma árvore binária vazia e devolve seu endereço*/
Arvore* cria_arvore() {

	Arvore* novo = (Arvore*) malloc(sizeof(Arvore*));

	novo->raiz = NULL;

	return novo;
}

/*Imprime os Elementos de uma Árvore binária de busca em inordem*/
void inordem (No* n) {
	if (n != NULL) {
		inordem(n->esq);
		printf("%d ", n->valor);
		inordem(n->dir);
	}
	return;
}

/*Imprime os Elementos de uma Árvore binária de busca em inordem*/
void preordem (No* n) {
	if (n != NULL) {
		printf("%d ", n->valor);
		preordem(n->esq);
		preordem(n->dir);
	}
	return;
}

/*Imprime os Elementos de uma Árvore binária de busca em inordem*/
void posordem (No* n) {
	if (n != NULL) {
		posordem(n->esq);
		posordem(n->dir);
		printf("%d ", n->valor);
	}
	return;
}

/*Busca um valor inteiro na árvore binária e devolve o endereço de seu nó, ou NULL se o valor procurado não estiver nela*/
No* busca(No* n, int v) {
	if (n != NULL) {
		if (v <n->valor) {
			return busca(n->esq, v);
		}
		else if (v> n->valor) {
			return busca(n->dir, v);
		}
		else if ( v == n->valor) {
			return n;
		}
	}
	return NULL;
}

/*Inesere um elemento em uma árvore binária de busca*/
void insere(Arvore* a, int elemento) {
	No* novo = (No*) malloc(sizeof(No*));
	novo->valor = elemento;
	novo->esq = NULL;
	novo->dir = NULL;


	if ( a->raiz == NULL) {
		a->raiz = novo;
	}
	else {
		No* atual = a->raiz;

		while( atual != NULL ) {
			if (elemento < atual->valor) {
				if (atual->esq == NULL) {
					atual->esq = novo;
					atual = NULL;
				}
				else {
					atual = atual->esq;
				}
			}
			else if (elemento >= atual->valor) {
				if (atual->dir == NULL) {
					atual->dir = novo;
					atual = NULL;
				}
				else {
					atual = atual->dir;
				}
			}
		}
	}
	return;	
}

/*Remove um elemento de uma árvore binária de busca. Se o elemento desejado não estiver nela, nada é feito*/
void remover (Arvore* a, int elemento){
	No* alvo = busca(a->raiz, elemento);

	No* pai = a->raiz;
	if (a->raiz != alvo) { // procuro pai do alvo apenas se o alvo nao for a raiz
		while(pai->esq != alvo && pai->dir != alvo) {
			if (elemento < pai->valor) {
				pai = pai->esq;
			}
			if (elemento > pai->valor) {
				pai = pai->dir;
			}
		}
	}

	if (alvo != NULL) { // alvo a ser removido esta presente na arvore
		if (alvo->esq == NULL && alvo->dir == NULL) { // alvo é uma folha
			//folha é removida da árvore
			if (pai->dir == alvo) {
				pai->dir = NULL;
				return;
			}
			if (pai->esq == alvo) {
				pai->esq = NULL;
				return;
			}
			if (a->raiz == alvo) {
				a->raiz = NULL;
				return;
			}
			free(alvo);
		}
		else { //alvo é um nó interno
			No* candidato, *pai_candidato;
			int flag; //flag = 1, candidato na esq ; flag = 2, candidato na dir
			if (alvo->esq != NULL) { //Primeiro verifico por uma subarvore à esquerda
				//Maior elemento da subárvore esquerda
				candidato = alvo->esq;
				pai_candidato = alvo;
				while (candidato->dir != NULL) {
					pai_candidato = candidato;
					candidato = candidato->dir;
				}
				flag = 1;
			}
			else { 
				//Menor elemento da subárvore direita
				candidato = alvo->dir;
				pai_candidato = alvo;
				while (candidato->esq != NULL) {
					pai_candidato = candidato;
					candidato = candidato->esq;
				}
				flag = 2;
			}

			if ( a->raiz != alvo) {
				//atualização do apontador do pai do alvo
				if (pai->dir == alvo) {
					pai->dir = candidato;
				}
				if (pai->esq == alvo) {
					pai->esq = candidato;
				}
			}
			else {//Caso a raiz esteja sendo removida, seu apontador deve ser atualizado 
				a->raiz = candidato;
			}

			if (flag == 1 && alvo != pai_candidato) {
				//toda a subarvore esquerda sobe um nível, caso haja uma
				if ( candidato->esq != NULL) { //candidato não é uma folha
					pai_candidato->dir = candidato->esq;
				}
				else { //candidato é uma folha
					pai_candidato->dir = NULL;
				}
			}
			else if (flag == 2 && alvo != pai_candidato) {
				//toda a subarvore direita sobe um nível, caso haja uma
				if ( candidato->dir != NULL) { //candidato não é uma folha
					pai_candidato->esq = candidato->dir;
				}
				else { //candidato é uma folha
					pai_candidato->esq = NULL;
				}
			}

			//candidato deve substituir o alvo a ser removido
			if ( alvo->esq != candidato){
				candidato->esq = alvo->esq;	
			}
			if ( alvo->dir != candidato){
				candidato->dir = alvo->dir;
			}

			free(alvo);
		}
	}
}

/*Remove a primeira folha que encontrar de uma árvore binária, dando prioridade para o lado esquedo da árvore e devole seu valor inteiro*/
int removefolha(No* n){
	No* alvo = n;
	No* pai = alvo;
	int devolver = alvo->valor;

	while (alvo->esq != NULL || alvo->dir != NULL) { //busca pelo pai do alvo
		pai = alvo;
		if (alvo->esq != NULL) {
			alvo = alvo->esq;
		}
		else if (alvo->dir != NULL) {
			alvo = alvo->dir;
		}
	}
	if (n == alvo) { //se estiver removendo a raiz
		n = NULL;
		free(alvo);
		return devolver;
	}
	else {//ponteiro do pai deve ficar nulo na direção do filho que esta sendo removido
		if( pai->dir == alvo) {
			pai->dir = NULL;
		}
		if( pai->esq == alvo) {
			pai->esq = NULL;
		}
		free(alvo);
		return devolver;
	}
}

/*Calcula a altura a altura de uma árvore binária e a devolve como um inteiro*/
int altura(No* n) {
	if (n->esq == NULL && n->dir == NULL) {
		return 0;
	}
	if (n->esq != NULL && n->dir != NULL) {
		int a = altura(n->esq) + 1;
		int b = altura(n->dir) + 1;
		if ( a< b) {
			return b;
		} 
	    return a;
	}
	if (n->esq != NULL) {
	    return altura(n->esq) + 1;
	}
	if (n->dir != NULL) {
	    return altura(n->dir) + 1;
	}
}

/*Recebe um inteiro que representa a qtd de elementos de uma árvore binária, calcula e devolve um inteiro representando a altura minima dessa árvore*/
int altmin(int n) {
	double elementos = log2((double)n);
	return (int) elementos;
}

/*Recebe um inteiro que representa a qtd de elementos de uma árvore binária, calcula e devolve um inteiro representando a altura minima dessa árvore*/
int altmin2(int n) {
	int i, a, b= 2;
	if ( n <= 1) {
		return 0;
	}
	for (i=1; i<n; i++) {
		b=2;
		for (a=1; a<=i; a++) {
			b= b*2;
		}
		if ( b > n) {
			return i;
		}
	}
	return -1;
}

/*Calcula a qtd de nós de uma árvore binária*/
int nodes(No* n) {
	if (n->esq == NULL && n->dir == NULL) {
		return 1;
	}
	if (n->esq == NULL) {
		return nodes(n->dir)+ 1;
	}
	if (n->dir == NULL) {
		return nodes(n->esq) + 1;
	}
	return nodes(n->esq) + nodes(n->dir) + 1;
}

/*Calcula a qtd de folhas de uma árvore binária*/
int leafs(No* n) {
	if (n->esq == NULL && n->dir == NULL) {
		return 1;
	}
	if (n->esq == NULL) {
		return leafs(n->dir);
	}
	if (n->dir == NULL) {
		return leafs(n->esq);
	}
	return leafs(n->esq) + leafs(n->dir);
}

/*Busca o nó pai do valor desejado*/
int pai(Arvore* a, int chave) {
	No* filho = busca(a->raiz, chave);
	No* pai = a->raiz;
	if (chave == pai->valor) {
		return -1;
	}
	if ( filho == NULL) {
		return -2;
	}
	while (pai->esq != filho && pai->dir != filho) {
		if (pai->valor > chave) {
			pai = pai->esq;
		}
		else if (pai->valor <= chave) {
			pai = pai->dir;
		}
	}
	return pai->valor;
}

void bubble_sort (int vetor[], int n) {
    int k, j, aux;

    for (k = 1; k < n; k++) {

        for (j = 0; j < n - 1; j++) {

            if (vetor[j] > vetor[j + 1]) {
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void reordena(No* n) {
	int nos = nodes(n);
	int fila[nos], fila1[ (nos/2) + 1], fila2[(nos/2)];

	int i;
	for (i=0; i<nos; i++) {
		int tmp = removefolha(n);
		fila[i] = tmp;

	}

	bubble_sort(fila, nos);

	if ( nos%2 == 0) {
		for (i = 0; i < nos/2; i++) {
			fila1[i] = fila[i];
		}
		for (i = 0; i<nos/2; i++) {
			fila2[i] = fila[i + (nos/2)];
		}

		for (i = 0; i < nos; i++) {
			insere(n,fila1[nos - i]);
			insere(n,fila2[i]);
		}
		return;
	} else {
		for (i = 0; i < (nos/2 + 1); i++) {
			fila1[i] = fila[i];
		}
		for (i = 0; i < nos/2; i++) {
			fila2[i] = fila[i + (nos/2 + 1)];
		}

		for (i = 0; i < nos; i++) {
			insere(n,fila1[nos - i]);
			insere(n,fila2[i]);
		}
		insere(n, fila1[ (nos/2) + 1]);
		return;
	}

}