#include <stdio.h>
#include <stdlib.h>
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
    int array_size = parameters->array_size;
    int *initial_array = parameters->initial_array;
    int *rank_array = parameters->rank_array;
    int *sorted_array = parameters->sorted_array;
    pthread_barrier_t* barrier = parameters->barrier;
    pthread_mutex_t* mutex = parameters->mutex;
	int i, j, r;

    for (i = 0; i < array_size; i++) {

        r = pthread_mutex_lock(mutex);

        if(r != 0) {
            printf("Error when locking mutex\n");
            exit(-1);
        }

        for (j = start; j < end; j++) {
            if (initial_array[j] < initial_array[i]) {
                rank_array[i]++;
            }
        }

        r = pthread_mutex_unlock(mutex);

        if(r != 0) {
            printf("Error when unlocking mutex\n");
            exit(-1);
        }

        r = pthread_barrier_wait(barrier);
        if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
            printf("Error when waiting for threads\n");
            exit(-1);
        }
    }

    if (thread_id == 0) {
        printf("Rank-uri:\n");
        for (i = 0; i < array_size; i++) {
            printf("%d ", rank_array[i]);
        }
        printf("\n");
    }


    for (i = start; i < end; i++) {
        sorted_array[i] = initial_array[rank_array[i]];
    }

    r = pthread_barrier_wait(barrier);
    if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
        printf("Error when waiting for threads\n");
        exit(-1);
    }

    if (thread_id == 0) {
        printf("Implementare paralela:\n");
        for (i = 0; i < array_size; i++) {
            printf("%d ", sorted_array[i]);
        }
        printf("\n");
    }
    
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    if (argc < 3) {
		fprintf(stderr, "Usage:\n\t./testapd array_size number_of_threads\n");
		return 0;
	}

    // Declaram bariera
    pthread_barrier_t barrier;

    // Declaram mutex
    pthread_mutex_t mutex;

    int i, j, r;
    int nr_threads = (int) strtol(argv[2], NULL, 10);
    int array_size = (int) strtol(argv[1], NULL, 10);

    int initial_array[array_size];
    int rank_array[array_size];
    int sorted_array[array_size];
    struct coreParameters parameters[nr_threads];

    for (i = 0; i < array_size; i++) {
        initial_array[i] = array_size - i + 5;
    }

    for (i = 0; i < array_size; i++) {
        rank_array[i] = 0;
    }

    /*for (i = 0; i < array_size; i++) {

        int howManySmall = 0;
        for (j = 0; j < array_size; j++) {
            if (initial_array[j] < initial_array[i]) {
                howManySmall++;
            }
        }
        rank_array[i] = howManySmall;
    }

    for (i = 0; i < array_size; i++) {
        sorted_array[i] = initial_array[rank_array[i]];
    }

    printf("Implementare seriala:\n");
    for (i = 0; i < array_size; i++) {
        printf("%d ", sorted_array[i]);
    }
    printf("\n");*/

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
        parameters[i].initial_array = initial_array;
        parameters[i].rank_array = rank_array;
        parameters[i].sorted_array = sorted_array;
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
