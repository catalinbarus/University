#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 8
#define MASTER 0

#define min(a,b) (((a) < (b)) ? (a) : (b))
 
int main(int argc, char * argv[]) {
	int rank, i, j;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	int start = rank * (double)N / nProcesses;
	int end = min((rank + 1) * (double)N / nProcesses, N);
	int v[8] = {6, 6, 6, 5, 9, 3, 2, 8};
	int toFind = -1;
	int nrApp = 0;

    if (rank == MASTER) {
		toFind = 6; 
    }

	MPI_Bcast(&toFind, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

	for (i = start; i < end; i++) {
        if(v[i] == toFind) {
			nrApp++;
		}
    }

	if(i != MASTER)
		MPI_Send(&nrApp, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);

	if(rank == 0) {
		for(int i = 1; i < nProcesses; i++) {
			int aux;
			MPI_Recv(&aux, 1, MPI_INT, i, 0, MPI_COMM_WORLD, NULL);
			nrApp += aux;
		}
		printf("%d apare de %d ori in vector", toFind, nrApp);
	} 

	MPI_Finalize();
	return 0;
}
