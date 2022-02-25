#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "testapd.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))

int cmp(const void *a, const void *b) {
	int A = *(int*)a;
	int B = *(int*)b;
	return A - B;
}

int cmpdesc(const void *a, const void *b) {
	int A = *(int*)a;
	int B = *(int*)b;
	return B - A;
}

void *thread_function(void *arg)
{
	struct coreParameters* parameters = (struct coreParameters*) arg;

    int thread_id = parameters->threadID;
    int nr_threads = parameters->numOfThreads;
    int start = parameters->start;
    int end = parameters->end;
    int array_size = parameters->array_size;
    int matrixLen = parameters->matrixLen;
    int **matrix = parameters->matrix;
    int *array = parameters->array;
    int *output_array = parameters->output_array;
    int *temp = parameters->temp;
    pthread_barrier_t* barrier = parameters->barrier;
    pthread_mutex_t* mutex = parameters->mutex;
	int i, j, k, r;

    if (thread_id == 0) {

        int idx = 0;
        for (i = 0; i < array_size / matrixLen + 1; i++) {

            for (j = 0; j < matrixLen; j++) {

                if (idx < array_size) {
                    printf("%d ", matrix[i][j]);
                    idx++;
                }
            }
            printf("\n");
        }

    }

    for(int k = 0; k < log(array_size) + 1; k++) {
        for(int i = thread_id; i < matrixLen; i += nr_threads) {
            if (i % 2) {
                qsort(matrix[i], matrixLen, sizeof(int), cmpdesc);
            } else {
                qsort(matrix[i], matrixLen, sizeof(int), cmp);
            }
        }

        
        pthread_barrier_wait(barrier);

        for (int i = thread_id; i < matrixLen; i += nr_threads) {
            int aux[matrixLen];
            for (int j = 0; j < matrixLen; j++) {
                aux[j] = matrix[j][i];
            }
            
            qsort(aux, matrixLen, sizeof(int), cmp);

            for (int j = 0; j < matrixLen; j++) {
                matrix[j][i] = aux[j];
            }
        }

        
        pthread_barrier_wait(barrier);
    }

    if (thread_id == 0) {

        int idx = 0;
        for (i = 0; i < matrixLen; i++) {

            for (j = 0; j < matrixLen; j++) {

               
                    printf("%d ", matrix[i][j]);
                    idx++;
                
            }
            printf("\n");
        }

    }

	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    if (argc < 3) {
		fprintf(stderr, "Usage:\n\t./testapd number_to_find number_of_threads\n");
		return 0;
	}

    // Declaram bariera
    pthread_barrier_t barrier;

    // Declaram mutex
    pthread_mutex_t mutex;

    int i, j, r;
    int nr_threads = (int) strtol(argv[2], NULL, 10);
    int matrixLen = (int) strtol(argv[1], NULL, 10);

    
    struct coreParameters parameters[nr_threads];

    int array_size = 8;
    int array[] = {6, 4, 16, 10, 16, 14, 2, 8};

    int **matrix = (int **) malloc(100 * sizeof(int));
    for (i = 0; i < 100; i++) {
        matrix[i] = (int *) malloc(100 * sizeof(int));
    }


    int idx = 0;
    int currentRow = 0;
    while (idx < array_size) {
        
        for (i = 0; i < matrixLen; i++) {
            matrix[currentRow][i] = array[idx + i];
        }
        idx += matrixLen;
        currentRow++;
    }

    /*idx = 0;
    for (i = 0; i < array_size / matrixLen + 1; i++) {

        for (j = 0; j < matrixLen; j++) {

            if (idx < array_size) {
                printf("%d ", matrix[i][j]);
                idx++;
            }
        }
        printf("\n");
    }*/
    int output_array[8];
    int temp[8];

    for (i = 0; i < array_size; i++) {
        output_array[i] = 0;
        temp[i] = 0;
    }

    output_array[0] = array[0];

	void *status;
	pthread_t threads[nr_threads];

	// Initializam bariera
	r = pthread_barrier_init(&barrier, NULL, nr_threads);

	if(r != 0) {
		printf("Eroare la initializarea barierei\n");
		exit(-1);
	}

    // Initializing the mutex
	r = pthread_mutex_init(&mutex, NULL);
	if(r != 0) {
        printf("Error when creating mutex\n");
        exit(-1);
    }

    int start, end;

	for (i = 0; i < nr_threads; i++) {
		
        // Calculating the start and end indexes for each subpart of the array
		start = i * (double)array_size / nr_threads;
		end = min((i + 1) * (double)array_size / nr_threads, array_size);

        parameters[i].start = start;
        parameters[i].end = end;
        parameters[i].threadID = i;
        parameters[i].numOfThreads = nr_threads;
        parameters[i].array_size = array_size;
        parameters[i].matrixLen = matrixLen;
        parameters[i].array = array;
        parameters[i].output_array = output_array;
        parameters[i].temp = temp;
        parameters[i].matrix = matrix;
        parameters[i].barrier = &barrier;
        parameters[i].mutex = &mutex;

		r = pthread_create(&threads[i], NULL, thread_function, (void *) &parameters[i]);

		if (r) {
			printf("Eroare la crearea thread-ului %d\n", i);
			exit(-1);
		}
	}

	for (i = 0; i < nr_threads; i++) {
		r = pthread_join(threads[i], &status);

		if (r) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}

	// Dezalocam bariera
	r = pthread_barrier_destroy(&barrier);

	if(r != 0) {
		printf("Eroare la distrugerea barierei\n");
		exit(-1);
	}

    // Free the mutex
	r= pthread_mutex_destroy(&mutex);
	if(r != 0) {
        printf("Error when destroying mutex\n");
        exit(-1);
    }

	return 0;
}
