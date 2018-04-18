#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 3
#define THREAD_LEN 20

typedef struct vetor
{
	int tam;
	int index;
	char* array;
} Vetor;

Vetor* criar_vetor (int tam)
{
	Vetor* v = (Vetor*) malloc (sizeof(Vetor));
	v->tam = tam;
	v->index = 0;
	v->array = malloc(sizeof(char) * tam);
	for(int i = 0; i<tam; i++)
	{
		v->array[i] = '-';
	}
	
	return v;
}

void printa_vetor(Vetor* v)
{
	for(int i = 0; i < v->tam; i++)
	{
		printf("%c", v->array[i]);
	}
	printf("\n");
}

void preencher_com_cuidado (Vetor* v)
{
	omp_lock_t lock;
	omp_init_lock(&lock);
#pragma omp parallel for schedule(static) num_threads(NUM_THREADS) shared(v)
	for (int i = 0; i < THREAD_LEN * NUM_THREADS; i++) 
	{
		omp_set_lock(&lock);
		int index = v->index;
		v->array[index] = 'A' + omp_get_thread_num();
		v->index++;
		omp_unset_lock(&lock);
  	}
}

void preencher_sem_cuidado (Vetor* v)
{
#pragma omp parallel for schedule(static) num_threads(NUM_THREADS) shared(v)
	for (int i = 0; i < THREAD_LEN * NUM_THREADS; i++) 
	{
		int index = v->index;
		v->array[index] = 'A' + omp_get_thread_num();
		v->index++;
  	}
}

int main ()
{
	Vetor* v1 = criar_vetor(NUM_THREADS * THREAD_LEN);
	Vetor* v2 = criar_vetor(NUM_THREADS * THREAD_LEN);
	Vetor* v3 = criar_vetor(NUM_THREADS * THREAD_LEN);

	preencher_sem_cuidado(v1);
	printf("Vetor sem mutex 1\n");
	printa_vetor(v1);
	preencher_sem_cuidado(v2);
	printf("Vetor sem mutex 2\n");
	printa_vetor(v2);
	preencher_com_cuidado(v3);
	printf("Vetor com mutex\n");
	printa_vetor(v3);
}
