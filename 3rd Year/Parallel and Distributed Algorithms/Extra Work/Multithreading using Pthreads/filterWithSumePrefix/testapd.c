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
    int numberToFind = parameters->numberToFind;
    int *array = parameters->array;
    int *output_array = parameters->output_array;
    int *temp = parameters->temp;
    int *bit_array = parameters->bit_array;
    pthread_barrier_t* barrier = parameters->barrier;
    pthread_mutex_t* mutex = parameters->mutex;
	int i, j, r;

    for (i = start; i < end; i++) {

        if (array[i] > 10) {
            bit_array[i] = 1;

        }
    }

    r = pthread_barrier_wait(barrier);
    if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
        printf("Error when waiting for threads\n");
        exit(-1);
    }

    if (thread_id == 0) {
        for (i = 0; i < array_size; i++) {
            printf("%d ", bit_array[i]);
        }
        printf("\n");
    }

    int d = 1;

    while(d < array_size) {
        temp[thread_id] = bit_array[thread_id];

        r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}

        if (thread_id - d >= 0) {
            bit_array[thread_id] = temp[thread_id - d] + bit_array[thread_id];
        }

        r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}

        d = 2 * d;
    }

    if (thread_id == 0) {
        for (i = 0; i < array_size; i++) {
            printf("%d ", bit_array[i]);
        }
        printf("\n");

        int nextNumber = 0;
        for (i = 0; i < array_size; i++) {
            if (bit_array[i] > nextNumber) {
                nextNumber = bit_array[i];
                printf("%d ", array[i]);
            }
        }
        printf("\n");
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
    int numberToFind = (int) strtol(argv[1], NULL, 10);

    
    struct coreParameters parameters[nr_threads];

    int array_size = 8;
    int array[] = {17, 4, 6, 11, 5, 13, 19, 24};
    int output_array[8];
    int temp[array_size];
    int bit_array[array_size];

    for (i = 0; i < array_size; i++) {
        output_array[i] = 0;
        temp[i] = 0;
        bit_array[i] = 0;
    }

    output_array[0] = array[0];

    /*for (i = 1; i < array_size; i++) {
        output_array[i] = array[i] + output_array[i - 1];
    }*/

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
        parameters[i].numberToFind = numberToFind;
        parameters[i].array = array;
        parameters[i].output_array = output_array;
        parameters[i].temp = temp;
        parameters[i].bit_array = bit_array;
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
