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
    int *array = parameters->array;
    pthread_barrier_t* barrier = parameters->barrier;
    pthread_mutex_t* mutex = parameters->mutex;
	int i, r;

    int start_odd_phase, start_even_phase;

	if (start % 2 == 0) {
		start_even_phase = start;
		start_odd_phase = start + 1;

	} else {
		start_even_phase = start + 1;
		start_odd_phase = start;

	}

    for (i = 0; i < array_size; i++) {

		// Incepem faza para
		for (int even_idx = start_even_phase; even_idx < end && (even_idx < array_size - 1); even_idx += 2) {

			if(array[even_idx] > array[even_idx + 1]) {
				int aux = array[even_idx];
				array[even_idx] = array[even_idx + 1];
				array[even_idx + 1] = aux;
			}

		}

		r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}

		// Incepem faza impara
		for (int odd_idx = start_odd_phase; odd_idx < end && (odd_idx < array_size - 1); odd_idx += 2) {

			if(array[odd_idx] > array[odd_idx + 1]) {
				int aux = array[odd_idx];
				array[odd_idx] = array[odd_idx + 1];
				array[odd_idx + 1] = aux;
			}

		}

		r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}
	}

    r = pthread_barrier_wait(barrier);
    if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
        printf("Error when waiting for threads\n");
        exit(-1);
    }

    if (thread_id == 0) {
        for (i = 0; i < array_size; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
		fprintf(stderr, "Usage:\n\t./testapd number_to_find number_of_threads\n");
		return 0;
	}

    // Declaram bariera
    pthread_barrier_t barrier;

    // Declaram mutex
    pthread_mutex_t mutex;

    int i, r;
    int nr_threads = (int) strtol(argv[1], NULL, 10);
   
    struct coreParameters parameters[nr_threads];

    int array_size = 8;
    int array[] = {6, 4, 16, 10, 16, 14, 2, 8};
   
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
        parameters[i].array = array;
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
