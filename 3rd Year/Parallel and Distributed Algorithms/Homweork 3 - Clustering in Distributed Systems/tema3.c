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

    if (rank == 0 || rank == 1 || rank == 2) {

        char file_name[100];
        char finalTopology[1000];
        int num_workers;
        int finalTopologySize;
        int start, end;

        /* Read the cluster file for the current coordinator */
        sprintf(file_name, "cluster%d.txt", rank);

        fp = fopen(file_name, "r");

        /* Parse the number of workers for current cluster */
        fscanf(fp, "%d", &num_workers);

        int my_workers[num_workers];

        /* Parse the workers for current cluster */
        for (int i = 0; i < num_workers; i++) {
            fscanf(fp, "%d", &my_workers[i]);
        }

        /* Inform its workers who is the coordinator */
        for (int i = 0; i < num_workers; i++) {
            MPI_Send(&rank, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, my_workers[i]);
        }

        if (rank == 0) {

            /* Send the number of workers and workers to process 1 */
            MPI_Send(&num_workers, 1, MPI_INT, 1, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 1);

            MPI_Send(&my_workers, num_workers, MPI_INT, 1, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 1);

            MPI_Recv(&finalTopologySize, 1, MPI_INT, 1, 15, MPI_COMM_WORLD, NULL);
            MPI_Recv(&finalTopology, finalTopologySize, MPI_CHAR, 1, 15, MPI_COMM_WORLD, NULL);

            printf("0 %s\n", finalTopology);

            /* Send topology to the workers */
            for (int i = 0; i < num_workers; i++) {
                MPI_Send(&finalTopologySize, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);

                MPI_Send(&finalTopology, finalTopologySize, MPI_CHAR, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
            }

            /* Build the initial array */
            int array_size = (int) strtol(argv[1], NULL, 10);
            int array[array_size];

            for (int i = 0; i < array_size; i++) {
                array[i] = i;
            }

            /* Compute start/end indexes for each cluster */
            for (int i = 2; i >= 0; i--) {

                start = i * (double)array_size / 3;
	            end = min((i + 1) * (double)array_size / 3, array_size);

                
                if (i != 0) {
                    MPI_Send(&start, 1, MPI_INT, i, 15, MPI_COMM_WORLD);
                    printf("M(%d,%d)\n", rank, i);

                    MPI_Send(&end, 1, MPI_INT, i, 15, MPI_COMM_WORLD);
                    printf("M(%d,%d)\n", rank, i);

                    MPI_Send(&array_size, 1, MPI_INT, i, 15, MPI_COMM_WORLD);
                    printf("M(%d,%d)\n", rank, i);

                    MPI_Send(&array, array_size, MPI_INT, i, 15, MPI_COMM_WORLD);
                    printf("M(%d,%d)\n", rank, i);
                }   
            }

            /* Move the subarray for the current cluster into an actual array */
            int processArray[end - start];

            int count = 0;
            for (int i = start; i < end; i++) {

                processArray[count] = array[i];
                count++;
            }

            /* Split the subarray for this cluster to each of its workers */
            for (int i = 0; i < num_workers; i++) {

                int startWorker = i * (double)(end - start) / num_workers;
                int endWorker = min((i + 1) * (double)(end - start) / num_workers, (end - start));

                MPI_Send(&startWorker, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
                MPI_Send(&endWorker, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);

                int size = end - start;
                MPI_Send(&size, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
                MPI_Send(&processArray, size, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);


            }

            /* Get the processed subarray from the workers */
            int receivedArray[end - start];
            int receivedIdx = 0;

            for (int i = 0; i < num_workers; i++) {

                int size;
                MPI_Recv(&size, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD, NULL);
                int receivedFragment[size];
                MPI_Recv(&receivedFragment, size, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD, NULL);

                for (int j = 0; j < size; j++) {

                    receivedArray[receivedIdx] = receivedFragment[j];
                    receivedIdx++;
                }
            }

            /* Build and display the processed array */
            int cluster1Size;
            MPI_Recv(&cluster1Size, 1, MPI_INT, 1, 15, MPI_COMM_WORLD, NULL);

            int cluster1Fragment[cluster1Size];
            MPI_Recv(&cluster1Fragment, cluster1Size, MPI_INT, 1, 15, MPI_COMM_WORLD, NULL);

            int cluster2Size;
            MPI_Recv(&cluster2Size, 1, MPI_INT, 2, 15, MPI_COMM_WORLD, NULL);

            int cluster2Fragment[cluster2Size];
            MPI_Recv(&cluster2Fragment, cluster2Size, MPI_INT, 2, 15, MPI_COMM_WORLD, NULL);

            printf("Rezultat: ");
            for (int i = 0; i < receivedIdx; i++) {
                printf("%d ", receivedArray[i]);
            }

            for (int i = 0; i < cluster1Size; i++) {
                printf("%d ", cluster1Fragment[i]);
            }

            for (int i = 0; i < cluster2Size; i++) {

                if (i != cluster2Size - 1) {
                    printf("%d ", cluster2Fragment[i]);
                }
                else {
                    printf("%d\n", cluster2Fragment[i]);
                }
            }
                 
        }

        if (rank == 1) {

           
            /* Receive the workers from coordinator 0*/
            int workersSize0;
            int fromWorkers0[100];
            MPI_Recv(&workersSize0, 1, MPI_INT, 0, 15, MPI_COMM_WORLD, NULL);
            MPI_Recv(&fromWorkers0, workersSize0, MPI_INT, 0, 15, MPI_COMM_WORLD, NULL);

            /* Receive the workers from coordinator 2*/
            int workersSize2;
            int fromWorkers2[100];
            MPI_Recv(&workersSize2, 1, MPI_INT, 2, 15, MPI_COMM_WORLD, NULL);
            MPI_Recv(&fromWorkers2, workersSize2, MPI_INT, 2, 15, MPI_COMM_WORLD, NULL);

            /* Build the topology */
            sprintf(finalTopology, "-> %d:", 0);
            for (int i = 0; i < workersSize0; i++) {

                if (i != workersSize0 - 1) {
                    sprintf(finalTopology + strlen(finalTopology), "%d,", fromWorkers0[i]);
                } 
                else {
                    sprintf(finalTopology + strlen(finalTopology), "%d ", fromWorkers0[i]);
                }
            }

            sprintf(finalTopology + strlen(finalTopology), "1:");
            for (int i = 0; i < num_workers; i++) {

                if (i != num_workers - 1) {
                    sprintf(finalTopology + strlen(finalTopology), "%d,", my_workers[i]);
                } 
                else {
                    sprintf(finalTopology + strlen(finalTopology), "%d ", my_workers[i]);
                }
            }

            sprintf(finalTopology + strlen(finalTopology), "2:");
            for (int i = 0; i < workersSize2; i++) {

                if (i != workersSize2 - 1) {
                    sprintf(finalTopology + strlen(finalTopology), "%d,", fromWorkers2[i]);
                } 
                else {
                    sprintf(finalTopology + strlen(finalTopology), "%d ", fromWorkers2[i]);
                }
            }

            printf("1 %s\n", finalTopology);

            /* Send the topology to coordinators 0 and 2 */
            finalTopologySize = strlen(finalTopology);
            MPI_Send(&finalTopologySize, 1, MPI_INT, 2, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 2);
            MPI_Send(&finalTopology, finalTopologySize, MPI_CHAR, 2, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 2);

            MPI_Send(&finalTopologySize, 1, MPI_INT, 0, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 0);
            MPI_Send(&finalTopology, finalTopologySize, MPI_CHAR, 0, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 0);

            /* Send the topology to the workers */
            for (int i = 0; i < num_workers; i++) {
                MPI_Send(&finalTopologySize, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
                MPI_Send(&finalTopology, finalTopologySize, MPI_CHAR, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
            }

            /* Get the start/end indexes for the array generated by process 0 */
            MPI_Recv(&start, 1, MPI_INT, 0, 15, MPI_COMM_WORLD, NULL);
            MPI_Recv(&end, 1, MPI_INT, 0, 15, MPI_COMM_WORLD, NULL);

            /* Get the array generated by process 0 */
            int array_size;
            MPI_Recv(&array_size, 1, MPI_INT, 0, 15, MPI_COMM_WORLD, NULL);
            int array[array_size];
            MPI_Recv(&array, array_size, MPI_INT, 0, 15, MPI_COMM_WORLD, NULL);

            /* Move the subarray for the current cluster into an actual array */
            int processArray[end - start];

            int count = 0;
            for (int i = start; i < end; i++) {

                processArray[count] = array[i];
                count++;
            }

            /* Split the subarray for this cluster to each of its workers */
            for (int i = 0; i < num_workers; i++) {

                int startWorker = i * (double)(end - start) / num_workers;
                int endWorker = min((i + 1) * (double)(end - start) / num_workers, (end - start));

                MPI_Send(&startWorker, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
                MPI_Send(&endWorker, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);

                int size = end - start;
                MPI_Send(&size, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
                MPI_Send(&processArray, size, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
            }

            /* Get the processed subarray from the workers */
            int receivedArray[end - start];
            int receivedIdx = 0;

            for (int i = 0; i < num_workers; i++) {

                int size;
                MPI_Recv(&size, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD, NULL);
                int receivedFragment[size];
                MPI_Recv(&receivedFragment, size, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD, NULL);

                for (int j = 0; j < size; j++) {

                    receivedArray[receivedIdx] = receivedFragment[j];
                    receivedIdx++;
                }
            }

            /* Send the subarray to process 0 */
            MPI_Send(&receivedIdx, 1, MPI_INT, 0, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 0);
            MPI_Send(&receivedArray, receivedIdx, MPI_INT, 0, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 0);
        }

        if (rank == 2) {
 
             /* Send the number of workers and workers to process 1 */
            MPI_Send(&num_workers, 1, MPI_INT, 1, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 1);
            MPI_Send(&my_workers, num_workers, MPI_INT, 1, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 1);

            MPI_Recv(&finalTopologySize, 1, MPI_INT, 1, 15, MPI_COMM_WORLD, NULL);
            MPI_Recv(&finalTopology, finalTopologySize, MPI_CHAR, 1, 15, MPI_COMM_WORLD, NULL);

            printf("2 %s\n", finalTopology);

            /* Send topology to the workers */
            for (int i = 0; i < num_workers; i++) {
                MPI_Send(&finalTopologySize, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
                MPI_Send(&finalTopology, finalTopologySize, MPI_CHAR, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
            }

            MPI_Recv(&start, 1, MPI_INT, 0, 15, MPI_COMM_WORLD, NULL);
            MPI_Recv(&end, 1, MPI_INT, 0, 15, MPI_COMM_WORLD, NULL);

            int array_size;
            MPI_Recv(&array_size, 1, MPI_INT, 0, 15, MPI_COMM_WORLD, NULL);
            int array[array_size];
            MPI_Recv(&array, array_size, MPI_INT, 0, 15, MPI_COMM_WORLD, NULL);

            /* Move the subarray for the current cluster into an actual array */
            int processArray[end - start];

            int count = 0;
            for (int i = start; i < end; i++) {

                processArray[count] = array[i];
                count++;
            }

            /* Split the subarray for this cluster to each of its workers */
            for (int i = 0; i < num_workers; i++) {

                int startWorker = i * (double)(end - start) / num_workers;
                int endWorker = min((i + 1) * (double)(end - start) / num_workers, (end - start));

                MPI_Send(&startWorker, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
                MPI_Send(&endWorker, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);

                int size = end - start;
                MPI_Send(&size, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
                MPI_Send(&processArray, size, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, my_workers[i]);
            }

            /* Get the processed subarray from the workers */
            int receivedArray[end - start];
            int receivedIdx = 0;

            for (int i = 0; i < num_workers; i++) {

                int size;
                MPI_Recv(&size, 1, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD, NULL);
                int receivedFragment[size];
                MPI_Recv(&receivedFragment, size, MPI_INT, my_workers[i], 15, MPI_COMM_WORLD, NULL);

                for (int j = 0; j < size; j++) {

                    receivedArray[receivedIdx] = receivedFragment[j];
                    receivedIdx++;
                }
            }

            /* Send the subarray to process 0 */
            MPI_Send(&receivedIdx, 1, MPI_INT, 0, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 0);
            MPI_Send(&receivedArray, receivedIdx, MPI_INT, 0, 15, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, 0);
        }

    } else {

        int my_coordinator = -1;
        char finalTopology[1000];
        int finalTopologySize;
        int startWorker, endWorker;

        /* Get the coordinator for current worker */
        MPI_Recv(&my_coordinator, 1, MPI_INT, MPI_ANY_SOURCE, 15, MPI_COMM_WORLD, NULL);

        /* Get final topology from coordinator */
        MPI_Recv(&finalTopologySize, 1, MPI_INT, my_coordinator, 15, MPI_COMM_WORLD, NULL);
        MPI_Recv(&finalTopology, finalTopologySize, MPI_CHAR, my_coordinator, 15, MPI_COMM_WORLD, NULL);

        /* Get start/end indexes from coordinator */
        MPI_Recv(&startWorker, 1, MPI_INT, my_coordinator, 15, MPI_COMM_WORLD, NULL);
        MPI_Recv(&endWorker, 1, MPI_INT, my_coordinator, 15, MPI_COMM_WORLD, NULL);

        /* Get subarray made for this worker */
        int fragmentSize;
        MPI_Recv(&fragmentSize, 1, MPI_INT, my_coordinator, 15, MPI_COMM_WORLD, NULL);
        int fragmentArray[fragmentSize];
        MPI_Recv(&fragmentArray, fragmentSize, MPI_INT, my_coordinator, 15, MPI_COMM_WORLD, NULL);

        /* Update the array */
        for (int i = startWorker; i < endWorker; i++) {

            fragmentArray[i] *= 2;
        }

        int sendArray[endWorker - startWorker];
        int count = 0;
        for (int i = startWorker; i < endWorker; i++) {

            sendArray[count] = fragmentArray[i];
            count++;
        }

        /* Send the array back to the coordinator */
        MPI_Send(&count, 1, MPI_INT, my_coordinator, 15, MPI_COMM_WORLD);
        printf("M(%d,%d)\n", rank, my_coordinator);

        MPI_Send(&sendArray, count, MPI_INT, my_coordinator, 15, MPI_COMM_WORLD);
        printf("M(%d,%d)\n", rank, my_coordinator);

        printf("%d %s\n", rank, finalTopology);
    }
    
    MPI_Finalize();
}

