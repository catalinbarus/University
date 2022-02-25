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

    if (rank == 0) {

        for (int i = 1; i <= 3; i++) {
            MPI_Send(&rank, 1, MPI_INT, i, 15, MPI_COMM_WORLD);
        }

        fp = fopen(argv[1], "r");

        int numWords;
        fscanf(fp, "%d", &numWords);
        
        int start1, end1;
        int start2, end2;
        int start3, end3;

        start1 = 0 * (double)numWords / 3;
	    end1 = min((0 + 1) * (double)numWords / 3, numWords);

        start2 = 1 * (double)numWords / 3;
	    end2 = min((1 + 1) * (double)numWords / 3, numWords);

        start3 = 2 * (double)numWords / 3;
	    end3 = min((2 + 1) * (double)numWords / 3, numWords);

        int size1 = end1 - start1;
        int size2 = end2 - start2;
        int size3 = end3 - start3;

        MPI_Send(&size1, 1, MPI_INT, 1, 15, MPI_COMM_WORLD);
        MPI_Send(&size2, 1, MPI_INT, 2, 15, MPI_COMM_WORLD);
        MPI_Send(&size3, 1, MPI_INT, 3, 15, MPI_COMM_WORLD);

        int count = 0;

        char line[10000];
        fgets(line, sizeof(line), fp);

        for (int i = start1; i < end1; i++) {

            fgets(line, sizeof(line), fp);
            line[strcspn(line, "\n")] = 0;
            
            int wordSize = strlen(line) - 1;

            MPI_Send(&wordSize, 1, MPI_INT, 1, 15, MPI_COMM_WORLD);
            MPI_Send(&line, wordSize, MPI_CHAR, 1, 15, MPI_COMM_WORLD);
        } 

        for (int i = start2; i < end2; i++) {

            fgets(line, sizeof(line), fp);
            line[strcspn(line, "\n")] = 0;
            
            int wordSize = strlen(line) - 1;

            MPI_Send(&wordSize, 1, MPI_INT, 2, 15, MPI_COMM_WORLD);
            MPI_Send(&line, wordSize, MPI_CHAR, 2, 15, MPI_COMM_WORLD);
        } 

        for (int i = start3; i < end3; i++) {

            fgets(line, sizeof(line), fp);
            line[strcspn(line, "\n")] = 0;
            
            int wordSize = strlen(line) - 1;

            MPI_Send(&wordSize, 1, MPI_INT, 3, 15, MPI_COMM_WORLD);
            MPI_Send(&line, wordSize, MPI_CHAR, 3, 15, MPI_COMM_WORLD);
        } 

    }

    if (rank == 1 || rank == 2 || rank == 3) {

       int my_coordinator;
       char vowels[] = "AEIOUaeiou";
       char consonants[] = "qwrtpysdfghjklzxcvbnmQWRTYPSDFGHJKLZXCVBNM";
       int nrVowels = 0;
       int nrConsonants = 0;
       MPI_Recv(&my_coordinator, 1, MPI_INT, MPI_ANY_SOURCE, 15, MPI_COMM_WORLD, NULL);

       int size;
       MPI_Recv(&size, 1, MPI_INT, my_coordinator, 15, MPI_COMM_WORLD, NULL);
   
       int wordSize;

       for (int i = 0; i < size; i++) {

            char recvWord[10000];
            MPI_Recv(&wordSize, 1, MPI_INT, my_coordinator, 15, MPI_COMM_WORLD, NULL);
            MPI_Recv(&recvWord, wordSize, MPI_CHAR, my_coordinator, 15, MPI_COMM_WORLD, NULL);

            if (rank == 3 && i == size - 1) {
                wordSize++;
            }

            for (int j = 0; j < wordSize; j++) {

                if (strchr(vowels, recvWord[j])) {
                    nrVowels++;
                }

                if (strchr(consonants, recvWord[j])) {
                    nrConsonants++;
                }
            }

            printf("[%d] %s\n", rank, recvWord);
        }

        printf("[%d] v=%d c=%d\n", rank, nrVowels, nrConsonants);

        MPI_Send(&nrVowels, 1, MPI_INT, 4, 15, MPI_COMM_WORLD);
        MPI_Send(&nrConsonants, 1, MPI_INT, 5, 15, MPI_COMM_WORLD); 
    }

    if (rank == 4) {

        int totalVowels = 0;
        for (int i = 1; i <= 3; i++) {
            int currentVowels;

            MPI_Recv(&currentVowels, 1, MPI_INT, i, 15, MPI_COMM_WORLD, NULL);
            totalVowels += currentVowels;
        }

        printf("[%d] Vowels: %d\n", rank, totalVowels);

    }

    if (rank == 5) {

        int totalConsonants = 0;
        for (int i = 1; i <= 3; i++) {
            int currentConsonants;

            MPI_Recv(&currentConsonants, 1, MPI_INT, i, 15, MPI_COMM_WORLD, NULL);
            totalConsonants += currentConsonants;
        }

        printf("[%d] Consonants: %d\n", rank, totalConsonants);

    }
    
    MPI_Finalize();
}

