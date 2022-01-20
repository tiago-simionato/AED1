#include "arvoreavl2.h"

/* Cria um nó de árvore binária vazia e devolve seu endereço*/
no* cria_no(int key) {
	no* novo = (no*) malloc(sizeof(no*));

	novo->valor = key;
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

/*Imprime os Elementos de uma Árvore binária de busca em inordem separados por um espaço branco. A função não pula linha*/
void inordem (no* n) {
	if (n != NULL) {
		inordem(n->esq);
		printf("%d ", n->valor);
		inordem(n->dir);
	}
	return;
}

/*Imprime os Elementos de uma Árvore binária de busca em preordem separados por um espaço branco. A função não pula linha*/
void preordem (no* n) {
	printf("(");
	if (n != NULL) {
		printf("%d", n->valor);
		if (n->esq != NULL || n->dir != NULL) {
			preordem(n->esq);
			preordem(n->dir);
		}
	}
	printf(")");
	return;
}

/*Imprime os Elementos de uma Árvore binária de busca em posordem separados por um espaço branco. A função não pula linha*/
void posordem (no* n) {
	printf("(");
	if (n != NULL) {
		if (n->esq != NULL || n->dir != NULL) {
			posordem(n->esq);
			posordem(n->dir);
		}
		printf("%d", n->valor);
	}
	printf(")");
	return;
}

/*Busca um valor inteiro na árvore binária e devolve o endereço de seu nó, ou NULL se o valor procurado não estiver nela*/
no* busca(no* root, int key) {
	if (root != NULL) {
		if (key < root->valor) {
			return busca(root->esq, key);
		}
		else if (key > root->valor) {
			return busca(root->dir, key);
		}
		else if ( key == root->valor) {
			return root;
		}
	}
	return NULL;
}

/*Inesere um elemento em uma árvore binária de busca*/
no* insere(no* root, int key) {
	//inserindo nó recursivamente
	if (root == NULL) {
		root = cria_no(key);
	}
	if (key == root->valor) {
		return root;
	}
	else {
		if (key < root->valor) {
			root->esq = insere(root->esq, key);
		}
		else {
			root->dir = insere(root->dir, key);
		}
	}
	
	//atualizando o balanceamento
	root = balanceador(root);
	return root;
}

/*Remove um elemento de uma árvore binária de busca. Se o elemento desejado não estiver nela, nada é feito*/
no* remover (no* root, int key) {
	no* target = busca(root, key);
	no* pai = paiend(root, target);

	if (target == NULL) { //alvo não está na arvore
		return;
	}

	if (target->esq == NULL && target->dir == NULL) { //alvo é uma folha
		if (pai != NULL) {
			if (pai->esq == target) {
				pai->esq = NULL;
			} 
			else {
				pai->dir = NULL;
			}
		}
		
		free(target);
	}
	else { //alvo é nó interno
		no* sub;
		if (target->esq != NULL) { //procuro maior elemento na subarvore esquerda
			sub = target->esq;
			while (sub->dir != NULL) {
				sub = sub->dir;
			}
			no* paisub = paiend(root, sub);
			if (paisub != target) {
				paisub->dir = NULL;
			}
			sub->dir = target->dir;
		}
		else if (target->dir != NULL) { //não há subarvore esquerda, então procuro menor elemento da direita
			sub = target->dir;
			while (sub->esq != NULL) {
				sub = sub->esq;
			}
			no* paisub = paiend(root, sub);
			if (paisub != target) {
				paisub->esq = NULL;
			}
			sub->esq = target->esq;
		}

		if (pai != NULL) {
			if (pai->esq == target) {
				pai->esq = sub;
			} 
			else if (pai->dir == target){
				pai->dir = sub;
			}
		}
		free(target);


		/*
		//rebalanceamento
		if (pai != NULL) {
			if (fator_balanceamento(pai)); {
				pai = balanceador(pai);
			}
			sub = balanceador(sub);
		}
		*/

		if (pai == root) {
			return pai;
		}
		else {
			return root;
		}
	}
}

/*Remove a primeira folha que encontrar de uma árvore binária, dando prioridade para o lado esquedo da árvore e devole seu valor inteiro*/
int removefolha(no* n){
	no* alvo = n;
	no* pai = alvo;
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

/* Calcula e devole a altura deum nó n */
int altura(no* n) {
	if (n != NULL) {
		if (n->esq == NULL && n->dir == NULL) {
			return 1;
		}
		if (n->esq != NULL && n->dir != NULL) {
			return max(altura(n->dir), altura(n->esq));
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

/*Calcula a quantidade de nós de uma árvore binária*/
int nodes(no* n) {
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

/*Calcula a quantidade de folhas de uma árvore binária*/
int leafs(no* n) {
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
int pai(no* root, int key) {
	no* filho = busca(root, key);
	no* pai = root;
	if (key == pai->valor) {
		return -1;
	}
	if ( filho == NULL) {
		return -2;
	}
	while (pai->esq != filho && pai->dir != filho) {
		if (pai->valor > key) {
			pai = pai->esq;
		}
		else if (pai->valor <= key) {
			pai = pai->dir;
		}
	}
	return pai->valor;
}

/* Busca o pai do nó desejado e retorna seu endereço. Retorna nulo caso o nó seja a raiz, ou se o filho procurado nao existir*/
no* paiend(no* root, no* filho) {
	if (filho == root || filho == NULL) {
		return NULL;
	}

	no* pai = root;
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
int fator_balanceamento(no* n) {
    if (n == NULL) {
		return 0;
	}
	return altura(n->dir) - altura(n->esq);
}

/*Realiza uma rotação para a esquerda*/
no* rotacaoEsq(no* a) {
	no* b = a->dir;
	no* c = b->esq;

	//rotation
	b->esq = a;
	a->dir = c;

	return b;
}

/*Realiza uma rotação para a direita*/
no* rotacaoDir(no* a) {
	no* b = a->esq;
	no* c = b->dir;

	//rotation
	b->dir = a;
	a->esq = c;

	return b;
}

/*Verifica necessidade de balanceamento da arvore e realiza as rotações caso necessário*/
no* balanceador(no* n) {
	int fb = fator_balanceamento(n);
	int fbl = fator_balanceamento(n->esq); 
	int fbr = fator_balanceamento(n->dir);

	if (fb > 1) {
		if (fbr > 0) {//RR
			return rotacaoEsq(n);
		}
		else if (fbl < 0) { //RL
			n->dir = rotacaoDir(n->dir);
			return rotacaoEsq(n);
		}
	}
	if (fb < -1) {
		if (fbl < 0) { //LL
			return rotacaoDir(n);
		}
		else if (fbr > 0) { //LR
			n->esq = rotacaoEsq(n);
			return rotacaoDir(n);
		}
	}
	return n;
}

int max(int a, int b){
	if (a > b) {
		return a;
	}
	return b;
}