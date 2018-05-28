/*
 *  Exemplo de programa para calculo de produto escalar em paralelo, usando POSIX threads.
 *  andrea@inf.ufsm.br
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mpi.h"

typedef struct 
 {
   double *a;
   double *b;
   double c; 
   int wsize;
   int repeat; 
 } dotdata_t;

// Variaveis globais, acessiveis por todas threads
dotdata_t dotdata;
// MPI
int myrank;         // "rank" do processo (0 a P-1)
int p;              // número de processos
int source;         // "rank" do processo remetente
int dest;           // "rank" do processo destinatário
int tag = 0;        // "etiqueta" da mensagem
char msg[100];      // a mensagem
MPI_Status status;  // "status" de uma operação efetuada

/*
 * Funcao executada por uma thread
 */
double dotprod_worker(int start, int end)
{
   int i, k;
   double *a = dotdata.a;
   double *b = dotdata.b;     
   double mysum;

   for (k = 0; k < dotdata.repeat; k++) {
      mysum = 0.0;
      for (i = start; i < end ; i++)  {
         mysum += (a[i] * b[i]);
      }
   }

   return mysum;
}


/* 
 * Distribui o trabalho entre nthreads
 */
void dotprod_threads()
{
	double sum = dotprod_worker(0, dotdata.wsize);
	sprintf(msg, "%f", sum);
	// envia mensagem ao processo 0
	dest = 0;
	MPI_Send(msg, strlen(msg)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
/*
   int i;
   pthread_t *threads;
   pthread_attr_t attr;

   threads = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
   pthread_mutex_init(&mutexsum, NULL);

   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   for (i = 0; i < nthreads; i++) {
      pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
   }
   pthread_attr_destroy(&attr);
   for (i = 0; i < nthreads; i++) {
      pthread_join(threads[i], NULL);
   }
   free(threads);
*/
}


/*
 * Tempo (wallclock) em microssegundos
 */ 
long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

/*
 * Preenche vetor
 */ 
void fill(double *a, int size, double value)
{  
   int i;
   for (i = 0; i < size; i++) {
      a[i] = value;
   }
}

/*
 * Funcao principal
 */ 
int main(int argc, char **argv)
{
   int wsize, repeat;
   long start_time, end_time;

   if ((argc != 3)) {
      printf("Uso: %s <worksize> <repetitions>\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   wsize = atoi(argv[1]);  // worksize = tamanho do vetor de cada thread
   repeat = atoi(argv[2]); // numero de repeticoes dos calculos (para aumentar carga)

   // Cria vetores
   dotdata.a = (double *) malloc(wsize * sizeof(double));
   fill(dotdata.a, wsize, 0.01);
   dotdata.b = (double *) malloc(wsize * sizeof(double));
   fill(dotdata.b, wsize, 1.0);
   dotdata.c = 0.0;
   dotdata.wsize = wsize;
   dotdata.repeat = repeat;



   float sum = 0;
   // Calcula c = a . b em p, medindo o tempo
   start_time = wtime();
   // MPI_Init deve ser invocado antes de qualquer outra chamada MPI
   MPI_Init(&argc, &argv);
   // Descobre o "rank" do processo
   MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
   // Descobre o número de processos
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   /////////////////////////////////////////////////////
	if (myrank != 0) 
	{
	    dotprod_threads();
	} 
	else
	{
		for(source = 1; source < p; source++)
		{
		// recebe P-1 mensagens
		MPI_Recv(msg, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
		sum += atof(msg);
			printf("%s\n", msg); // mostra mensagem
		}
	   // Mostra resultado e estatisticas da execucao
	   printf("Soma total: %f\n", sum);
   		end_time = wtime();
	   printf("%d thread(s), %ld usec\n", p - 1, (long) (end_time - start_time));
	   fflush(stdout);
	}
   /////////////////////////////////////////////////////
   MPI_Finalize(); // finaliza MPI






   free(dotdata.a);
   free(dotdata.b);

   return EXIT_SUCCESS;
}

