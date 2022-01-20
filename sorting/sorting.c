#include "sorting.h"

int main () {

	return 0;
}

/*Organiza um vetor utilizando a lógica do Bubblesort. n é o tamanho do vetor*/
void bubblesort(int *v, int n) {
	int i,j;
	for (i=0; i < n-1; i++) {

		for (j=n-1; j > i ; j--) {
			if (v[j] < v[j-1]) {
				int tmp = v[j];
				v[j] = v[j-1];
				v[j-1] = tmp;
			}
		}
	}
}

/*Organiza um vetor utilizando a lógica do Selectionsort. n é o tamanho do vetor*/
void selectionsort(int *v, int n) {
	int i,j;
	for (i = 0; i < n; i++) {

		int menor = i;
		for (j = i; j < n; j++) {

			if (v[j] < v[menor]) {
				menor = j;
			}
		}
		if (menor != i) {
			int tmp = v[menor];
			v[menor] = v[i];
			v[i] = tmp;
		}
	}
}

/*Organiza parcialmente um vetor utilizando a lógica do Selectionsort. n é o tamanho do vetor. Ao final, apenas os k primeiros elementos do vetor estarão ordenados e eles serão os k menores elementos do vetor todo. Se k receber um valor maior que n, nada é feito*/
void partialselectionsort(int *v, int n, int k) {
	if (k <= n) {
		int i,j;
		for (i = 0; i < k; i++) {

			int menor = i;
			for (j = i; j < n; j++) {
			
				if (v[j] < v[menor]) {
					menor = j;
				}
			}
			if (menor != i) {
				int tmp = v[menor];
				v[menor] = v[i];
				v[i] = tmp;
			}
		}
	}
}

/*Organiza um vetor utilizando a lógica do Insertionsort. n é o tamanho do vetor*/
void insertionsort(int *v, int n) {
    int i,j,tmp;
    for (i = 1; i < n; i++) {
        
        tmp = v[i];
        for (j = i-1; j >= 0 && v[j] > tmp; j--) {
                v[j+1] = v[j];
                v[j] = tmp;
                imprime(v, n);
        }
        v[j+1] = tmp;
    }
}

/*Organiza um vetor utilizando a lógica do Mergesort. p é o indice de onde deve começar a ordenação do vetor e r é o indice de onde ela deve terminar*/
void mergesort (int* v. int p, int r) {
	if (p < r-1) {
		q = (p + r)/2;
		mergesort(v, p, q);
		mergesort(v, q + 1, r);
		intercala_merge(v, p, q, r);
	}
}

/*Função utilizada pelo Mergesort para organizar um vetor*/
void intercala_merge(int* v, int p, int q, int r) {

}

/*Organiza um vetor utilizando a lógica do Quicksort. p é o indice de onde deve começar a ordenação do vetor e r é o indice de onde ela deve terminar
void quicksort(int* v, int p , int r) {
	int j;

	if (p < r) {
		j = particiona (v, p, r);
		quicksort(v, p, j-1);
		quicksort(v, j+1, r);
	}
}

void quicksortcomp(int* v, int p , int r, int * comp) {
	int j;

	if (p < r) {
		j = particionacomp(v, p, r, comp);
		quicksortcomp(v, p, j-1, comp);
		quicksortcomp(v, j+1, r, comp);
	}
}

/*Função utilizada pelo Quicksort para organizar um vetor*/
int particiona_quick (int* v, int p, int r) {
	int j, pivo, k;
	pivo = v[r];
	j = p;
	for (k=p; k < r; k++)f
		if (v[k] <= pivo)f
			troca (v[k], v[j]);
			j++;
		}
	}

	int tmp = v[j];
	v[j] = pivo;
	pivo = tmp; 

	return j;
}

int particionacomp (int* v, int p, int r, int* comp) {
	int j, pivo, k;

	pivo = v[r];
	j = p;

	for (k=p; k < r; k++){
		*comp++;
		if (v[k] <= pivo){
			int tmp = v[k];
			v[k] = v[j];
			v[j] = tmp;

			j++;
		}
	}

	int tmp2 = v[j];
	v[j] = pivo;
	pivo = tmp2;

	return j;
}