#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
	int myrank;         // "rank" do processo (0 a P-1)
	int p;              // n�mero de processos
	int source;         // "rank" do processo remetente
	int dest;           // "rank" do processo destinat�rio
	int tag = 0;        // "etiqueta" da mensagem
	int maxsize = 10;
	char msg[maxsize];	
	MPI_Status status;  // "status" de uma opera��o efetuada

	// MPI_Init deve ser invocado antes de qualquer outra chamada MPI
	MPI_Init(&argc, &argv);
	// Descobre o "rank" do processo
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	// Descobre o n�mero de processos
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	// Inicia o contador somente no primeiro processo.
	if (myrank == 0)
	{
		strcpy(msg, "0");
	}
	// O primeiro processo não recebe mensagem nenhuma.
	if (myrank != 0)
	{
		source = myrank - 1;
		printf("%d receving from %d\n", myrank, source);
		MPI_Recv(msg, maxsize, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
		printf("msg: %s\n", msg);
	}
	// Não manda adiante se é o ultimo processo.
	if (myrank != p - 1)
	{
		int cont = atoi(msg);
		cont += 1;
		sprintf(msg, "%d", cont);
		dest = myrank + 1;
		MPI_Send(msg, strlen(msg)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	}
	if (myrank == p - 1)
	{
		int count = atoi(msg);
		printf("O resultado final eh %d\n", count);
	}

	MPI_Finalize(); // finaliza MPI
	return 0;
}

