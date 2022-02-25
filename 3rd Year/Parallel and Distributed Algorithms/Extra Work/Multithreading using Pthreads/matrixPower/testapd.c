#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "testapd.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))

void *thread_function(void *arg)
{
	struct coreParameters* parameters = (struct coreParameters*) arg;

    int thread_id = parameters->threadID;
    int nr_threads = parameters->numOfThreads;
    int start = parameters->start;
    int end = parameters->end;
    int matrixLen = parameters->matrixLen;
    int power = parameters->power;
    long **matrix = parameters->matrix;
    long **matrix_copy = parameters->matrix_copy;
    long **result = parameters->result;
    pthread_barrier_t* barrier = parameters->barrier;
    pthread_mutex_t* mutex = parameters->mutex;
	int i, j, k, r;

    if (thread_id == 0) {

        for (i = 0; i < matrixLen; i++) {

            for (j = 0; j < matrixLen; j++) {

                printf("%ld ", matrix[i][j]);  
            }
            printf("\n");
        }
    }

    int step = 1;

    while (step < power) {

        if (thread_id == 0) {
            for (int idx1 = 0; idx1 < matrixLen; idx1++) {
                for (int idx2 = 0; idx2 < matrixLen; idx2++) {
                    result[idx1][idx2] = 0;
                }
            }
        }

        r = pthread_barrier_wait(barrier);
        if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
            printf("Error when waiting for threads\n");
            exit(-1);
        }

        for (i = 0; i < matrixLen; i++) {
            for (j = 0; j < matrixLen; j++) {

                long helper_sum = 0;

                // Incrementam toata suma de pe for-ul interior intr-un helper
                // pentru ca aceasta sa nu se piarda
                if (step == 1) {
                    for (int k = start; k < end; k++) {
                        helper_sum += matrix[i][k] * matrix[k][j];
                    }
                }

                else {
                    for (int k = start; k < end; k++) {
                        helper_sum += matrix_copy[i][k] * matrix[k][j];
                    }

                }

                r = pthread_barrier_wait(barrier);
                if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
                    printf("Error when waiting for threads\n");
                    exit(-1);
                }

                // Pentru a ne asigura ca matricea c la un
                // anumit moment de timp primeste o singura valoare
                // ce nu va fi suprascrisa, blocam executia cu un mutex
                r = pthread_mutex_lock(mutex);

                if(r != 0) {
                    printf("Eroare la inchiderea mutex-ului\n");
                    exit(-1);
                }

                result[i][j] += helper_sum;

                r = pthread_mutex_unlock(mutex);

                if(r != 0) {
                    printf("Eroare la deschiderea mutex-ului\n");
                    exit(-1);
                }

                r = pthread_barrier_wait(barrier);
                if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
                    printf("Error when waiting for threads\n");
                    exit(-1);
                }
            }
        }

        if (thread_id == 0) {
            for (int idx1 = 0; idx1 < matrixLen; idx1++) {
                for (int idx2 = 0; idx2 < matrixLen; idx2++) {
                    matrix_copy[idx1][idx2] = result[idx1][idx2];
                }
            }
        }

        r = pthread_barrier_wait(barrier);
        if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
            printf("Error when waiting for threads\n");
            exit(-1);
        }

        step++;
    }

    r = pthread_barrier_wait(barrier);
    if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
        printf("Error when waiting for threads\n");
        exit(-1);
    }

    if (thread_id == 0) {

        for (i = 0; i < matrixLen; i++) {

            for (j = 0; j < matrixLen; j++) {

                printf("%ld ", result[i][j]);  
            }
            printf("\n");
        }
    }

	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    if (argc < 4) {
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
    int power = (int) strtol(argv[3], NULL, 10);
    
    struct coreParameters parameters[nr_threads];

    long **matrix = malloc(matrixLen * sizeof(long *));
    for (i = 0; i < matrixLen; i++) {
        matrix[i] = malloc(matrixLen * sizeof(long));
    }

    for (i = 0; i < matrixLen; i++) {
        for (j = 0; j < matrixLen; j++) {
            matrix[i][j] = 1 + i * matrixLen + j;
        }
    }

    long **matrix_copy = malloc(matrixLen * sizeof(long *));
    for (i = 0; i < matrixLen; i++) {
        matrix_copy[i] = malloc(matrixLen * sizeof(long));
    }

    for (i = 0; i < matrixLen; i++) {
        for (j = 0; j < matrixLen; j++) {
            matrix_copy[i][j] = 1 + i * matrixLen + j;
        }
    }

    long **result = malloc(matrixLen * sizeof(long *));
    for (i = 0; i < matrixLen; i++) {
        result[i] = malloc(matrixLen * sizeof(long));
    }

    for (i = 0; i < matrixLen; i++) {
        for (j = 0; j < matrixLen; j++) {
            result[i][j] = 0;
        }
    }

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
		start = i * (double)matrixLen / nr_threads;
		end = min((i + 1) * (double)matrixLen / nr_threads, matrixLen);

        parameters[i].start = start;
        parameters[i].end = end;
        parameters[i].threadID = i;
        parameters[i].numOfThreads = nr_threads;
        parameters[i].matrixLen = matrixLen;
        parameters[i].power = power;
        parameters[i].matrix = matrix;
        parameters[i].matrix_copy = matrix_copy;
        parameters[i].result = result;
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
