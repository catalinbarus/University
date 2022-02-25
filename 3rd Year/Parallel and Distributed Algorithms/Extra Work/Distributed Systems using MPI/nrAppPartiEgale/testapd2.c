#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b) (((a) < (b)) ? (a) : (b))

int main (int argc, char *argv[])
{
    int  numtasks, rank;
    FILE *fp;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int globalVector[8];
    int recvArray[8 / numtasks];

    if (rank == 0) {
        
        int v[8] = {1, 1, 4, 1, 2, 1, 6, 1};        
        memcpy(globalVector, v, sizeof(v));
    }

    MPI_Scatter(globalVector, 8 / numtasks, MPI_INT, recvArray, 8 / numtasks, MPI_INT, 0, MPI_COMM_WORLD);

    int count = 0;
    for (int i = 0; i < 8 / numtasks; i++) {

        if (recvArray[i] == 1) {
            count++;
        }
    }

    if (rank != 0) {

        MPI_Send(&count, 1, MPI_INT, 0, 15, MPI_COMM_WORLD);
    }

    if (rank == 0) {

        int recvSum;

        for (int i = 1; i < numtasks; i++) {

            MPI_Recv(&recvSum, 1, MPI_INT, i, 15, MPI_COMM_WORLD, NULL);
            count += recvSum;
        }

        printf("%d\n", count);
    }
    
    MPI_Finalize();
}

