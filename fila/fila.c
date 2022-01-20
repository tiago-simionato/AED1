#include "fila.h"


/*   Função que cria e devolve o endereço de uma fila. 
     A fila criada estará vazia, com o inicio igual a NULL. */
Fila* cria_fila(){
	Fila* nova = (Fila*) malloc(sizeof(Fila*));
	
	nova->inicio = NULL;
	
	return nova;
}

/* Verifica se a fila enviada como parâmetro está vazia ou não.
   Devolve 1 se a fila estiver vazia, ou 0, caso contrário */
int fila_vazia(Fila* F){
	if (F->inicio == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

/* Função que realiza a inclusão de um elemento no fim da fila. */
void enfileira (Fila* F, int n){
	No* elemento = (No*) malloc(sizeof(No*));
	
	elemento->valor=n;
	elemento->prox = NULL;
	
	
	if (F->inicio == NULL) {
		F->inicio = elemento;
	}
	else {
		No* tmp = F->inicio;
		while (tmp->prox != NULL) {
			tmp = tmp->prox;
		}
		
		tmp->prox = elemento;
	}
}

/* Função que devolve o elemento do inicio da fila após sua remoção.
   Deve liberar a memória após de desenfileiramento. Se a fila estiver
   vazia, deve devolver -1                                   */
int desenfileira (Fila* F){
	if (F->inicio == NULL) {
		return -1;
	} else {
		No* tmp = F->inicio;
		int removido = tmp->valor;
	
		F->inicio = tmp->prox;
    	free(tmp);
		return removido;
	}
}

/* Função que retorna o elemento que está no inicio da fila, mas sem
   remove-lo. Se a pilha estiver vazia, devolve -1.      */
int inicio_fila (Fila* F){
	No* tmp = F->inicio;
	if (F->inicio == NULL) {
		return -1;
	}
	return tmp->valor;
    
}

/* Função que mostra os elementos da fila passada como parâmetro.
   Imprime os elementos da fila iniciando por seu inicio, separados
   por um espaço branco. Imprime uma quebra de linha no final.
                                                                  */
void imprime (Fila* F){
	No* tmp = F->inicio;
	if (tmp != NULL) {
		printf("%d ", tmp->valor);
		while(tmp->prox != NULL) {
			tmp = tmp->prox;
			printf("%d ", tmp->valor);
		}
		printf("\n");
	}
}