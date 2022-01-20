#include <stdio.h>
#include <stdlib.h>
#include "arvoreavl.h"
#include <string.h>

/* Cria uma árvore binária vazia e devolve seu endereço*/
Arvore* cria_arvore() {

	Arvore* novo = (Arvore*) malloc(sizeof(Arvore*));

	novo->raiz = NULL;

	return novo;
}

/*Imprime os Elementos de uma Árvore binária de busca em inordem separados por um espaço branco. A função não pula linha*/
void inordem (No* n) {
	if (n != NULL) {
		inordem(n->esq);
		printf("%d ", n->valor);
		inordem(n->dir);
	}
	return;
}

/*Imprime os Elementos de uma Árvore binária de busca em preordem separados por um espaço branco. A função não pula linha*/
void preordem (No* n) {
	if (n != NULL) {
		printf("%d ", n->valor);
		preordem(n->esq);
		preordem(n->dir);
	}
	return;
}

/*Imprime os Elementos de uma Árvore binária de busca em posordem separados por um espaço branco. A função não pula linha*/
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
			else if (elemento > atual->valor) {
				if (atual->dir == NULL) {
					atual->dir = novo;
					atual = NULL;
				}
				else {
					atual = atual->dir;
				}
			}
			else if ( elemento == atual->valor) {
				novo = NULL;
				atual = NULL;
			}
		}

		if (novo != NULL) {
			atual = novo;
			balanceador(a, atual);
		}
	}
	return;	
}

/*Remove um elemento de uma árvore binária de busca. Se o elemento desejado não estiver nela, nada é feito*/
void remover (Arvore* a, int elemento){
	No* alvo = busca(a->raiz, elemento);
	
	if (alvo == NULL) {
		return;
	}

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
			}
			if (pai->esq == alvo) {
				pai->esq = NULL;
			}
			if (a->raiz == alvo) {
				a->raiz = NULL;
			}
			
			balanceador(a, pai);
			free(alvo);
			return;
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
            
            
			balanceador(a, pai);
			free(alvo);
		}
	}
}

/*Remove a primeira folha que encontrar de uma árvore binária, dando prioridade para o lado esquedo da árvore e devole seu valor inteiro*/
int removefolha(No* n){
	No* alvo = n;
	No* pai = alvo;
	int devolver = alvo->valor;

	while (alvo->esq != NULL || alvo->dir != NULL) { //busca por uma folha
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

int altura(No* n) {
	if (n != NULL) {
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
	return 0;
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
	if (n != NULL) {
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
	return 0;
}

/*Calcula a qtd de folhas de uma árvore binária*/
int leafs(No* n) {
	if (n != NULL) {
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
	return 0;
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

/* Busca o pai do nó desejado e retorna seu endereço. Retorna o próprio nó caso ele seja a raiz*/
No* paiend(No* raiz, No* filho) {
	if (filho == raiz) {
		return raiz;
	}

	No* pai = raiz;
	while (pai->esq != filho && pai->dir != filho) {
		if (pai->valor > filho->valor) {
			pai = pai->esq;
		}
		else if (pai->valor <= filho->valor) {
			pai = pai->dir;
		}
	}
	return pai;
}

/*Retorna o valor do fator de balanceamento de uma árvore avl*/
int fator_balanceamento(No* n) {
    if (n->dir == NULL && n->esq == NULL) {
        return altura(n->dir) - altura(n->esq);
    }
    if (n->esq == NULL) {
        return (altura(n->dir)+1) - altura(n->esq);
    }
    if (n->dir == NULL) {
        return altura(n->dir) - (altura(n->esq)+1);
    }
	return (altura(n->dir)+1) - (altura(n->esq)+1);
}

/*Retorna 1 se o nó está desbalanceado ou 0 se não estiver*/
int desbalanceado(No* n) {
	if (fator_balanceamento(n) > 1 || fator_balanceamento(n) < -1) {
		return 1;
	}
	return 0;
}

void rotacaoesq(Arvore* a, No* atual) {
	if (atual == a->raiz) {
		a->raiz = atual->dir;

		No* filho = atual->dir;
		atual->dir = filho->esq;

		filho->esq = atual;
		return;
	} else {
		No* pai = paiend(a->raiz, atual);
		if (pai->dir == atual) {
			pai->dir = atual->dir;
		}
		if (pai->esq == atual) {
			pai->esq = atual->dir;
		}

		No* filho = atual->dir;
		atual->dir = filho->esq;

		filho->esq = atual;
		return;
	}
}

void rotacaodir(Arvore* a, No* atual) {
	if (atual == a->raiz) {
		a->raiz = atual->esq;

		No* filho = atual->esq;
		atual->esq = filho->dir;

		filho->dir = atual;
		return;
	} else {
		No* pai = paiend(a->raiz, atual);
		if (pai->dir == atual) {
			pai->dir = atual->esq;
		}
		if (pai->esq == atual) {
			pai->esq = atual->esq;
		}

		No* filho = atual->esq;
		atual->esq = filho->dir;

		filho->dir = atual;
		return;
	}
}

void balanceador(Arvore* a, No*atual) {
	//rastreamento à procura de nós desbalanceados
	while(desbalanceado(atual) == 0 && atual != a->raiz) {
		atual = paiend(a->raiz, atual);
	}

	//caso haja necessidade, fazer rotações
	if (desbalanceado(atual) == 1) {
    			
		if ( fator_balanceamento(atual) > 1) {
			if (fator_balanceamento(atual->dir) >= 0) { //rotacao simples
				rotacaoesq(a, atual);
			}
			else if (fator_balanceamento(atual->dir) < 0) {//rotacao dupla
				No* filho = atual->dir;
    
				rotacaodir(a, filho);
    					
				rotacaoesq(a, atual);
    			}
		}
		if ( fator_balanceamento(atual) < -1) {
			if (fator_balanceamento(atual->esq) <= 0) {//rotacao simples
				rotacaodir(a, atual);
			}
			else if (fator_balanceamento(atual->esq) > 0) {//rotacao dupla
    				
				No* filho = atual->esq;
    				
				rotacaoesq(a, filho);
				
				rotacaodir(a, atual);
			}
		}
	}
}

no* rotacaoADireita(no* y) {
    no* x  = y->esq;
    no* T2 = x->dir;
    
    // rotacao
    x->dir = y;
    y->esq = T2;
    
    // atualizacao de altura
    y->altura = 1 + max( altura(y->esq) , altura(y->dir) );
    x->altura = 1 + max( altura(x->esq) , altura(x->dir) );
    
    return x;
}

no* rotacaoAEsquerda(no* x) {
    no* y = x->dir;
    no* T2 = y->esq;

    //fazendo a rotacao
    x->esq = y;
    y->dir = T2;

    // atualizando a altura
    y->altura = 1 + max(altura(y->esq), altura(y->dir));
    x->altura = 1 + max(altura(x->esq), altura(x->dir));
}