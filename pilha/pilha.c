#include "pilha.h"

/*   Função que cria e devolve o endereço de uma pilha. 
     A pilha criada estará vazia, com o topo igual a NULL. */
Pilha* cria_pilha(){
	Pilha* nova = (Pilha*) malloc(sizeof(Pilha*));

	nova->topo = NULL;
	
	return nova;
}

/* Verifica se a pilha enviada como parâmetro está vazia ou não.
   Devolve 1 se a pilha estiver vazia, ou 0, caso contrário */
int pilha_vazia(Pilha* P){
	if (P->topo == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

/* Função que realiza a inclusão de um elemento na pilha. O
   elemento sempre é colocado no topo da pilha               */
void empilha (Pilha* P, int n){
	No* elemento = (No*) malloc(sizeof(No*));
	
	elemento->valor=n;
	elemento->prox = P->topo;
	
	P->topo = elemento;
}

/* Função que devolve o elemento do topo da pilha após desempilha-lo.
   Deve liberar a memória após de desempilhamento. Se a pilha estiver
   vazia, deve devolver -1                                   */
int desempilha (Pilha* P){
	if (P->topo == NULL) {
		return -1;
	} else {
		No* tmp = P->topo;
		int removido = tmp->valor;
		
		tmp = tmp->prox;
	
		free(P->topo);
		P->topo = tmp;
	
		return removido;
	}
}

/* Função que retorna o elemento que está no topo da pilha, mas sem
   desempilha-lo. Se a pilha estiver vazia, devolve -1.      */
int topo (Pilha* P){
	if (P->topo == NULL) {
		return -1;
	}
	No* tmp = P->topo;
	return tmp->valor;
}

/* Função que mostra os elementos da pilha passada como parâmetro.
   Imprime os elementos da pilha iniciando por seu topo, separados
   por um espaço branco. Imprime uma quebra de linha no final.                                    */
void imprime (Pilha* P){
	No* tmp = P->topo;
	if (tmp != NULL) {
		printf("%d ", tmp->valor);
		while(tmp->prox != NULL) {
			tmp = tmp->prox;
			printf("%d ", tmp->valor);
		}
		printf("\n");
	}
}