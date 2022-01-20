#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <stdlib.h>

void bubblesort(int *v, int n);

void selectionsort(int *v, int n);

void partialselectionsort(int *v, int n, int k);

void insertionsort(int *v, int n);

void mergesort(int* v, int p, int r);

void intercala_merge(int* v, int p, int q, int r);

void quicksort(int* v, int p, int r);

int particiona_quick (int* v, int p, int r);

#endif