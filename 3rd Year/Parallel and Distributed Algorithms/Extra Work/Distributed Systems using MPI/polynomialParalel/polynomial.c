#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MASTER 0

int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	//printf("Hello from %i/%i\n", rank, nProcesses);

    float *v_send = NULL; // full vector
    float *v_recv = (float *)malloc(1 * sizeof(float)); // partial vector
	
	//valoarea pt care trebuie calculat polinomul
	float x = 5;
	
	
	if (rank == MASTER) { 
		int polynomialSize, n;

		/*
			in fisierul de intrare formatul este urmatorul:
			numarul_de_coeficienti
			coeficient x^0
			coeficient x^1
			etc.
		*/

		FILE * polFunctionFile = fopen(argv[1], "rt");
		fscanf(polFunctionFile, "%d", &polynomialSize);
		/*
			in array-ul a se vor salva coeficientii ecuatiei / polinomului
			de exemplu: a = {1, 4, 4} => 1 * (x ^ 2) + 4 * (x ^ 1) + 4 * (x ^ 0)
		*/
		v_send = (float*)malloc(sizeof(float)*polynomialSize);
		for (int i = 0; i < polynomialSize; i++) {
			fscanf(polFunctionFile, "%f", &v_send[i]);
		}
		fclose(polFunctionFile);

	}

	//se imparte sarcinile
	MPI_Scatter(v_send, 1, MPI_FLOAT, v_recv, 1, MPI_FLOAT, MASTER, MPI_COMM_WORLD);
	
	if(rank != 0)
		v_recv[0] = v_recv[0] * pow(x, rank);
	

	MPI_Gather(v_recv, 1, MPI_FLOAT, v_send, 1, MPI_FLOAT, MASTER, MPI_COMM_WORLD);
		
	
	if (rank == MASTER)
    {
		float sum = 0;
        int j = 0;
        for (; j < nProcesses; ++j)
        {
            sum += v_send[j];
        }
		printf("Rezultatul este: %f", sum);
    }

	MPI_Finalize();
	return 0;
}
