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
    int *upperBound = parameters->upperBound;
    int *rightThread = parameters->rightThread;
    int *array = parameters->array;
    pthread_barrier_t* barrier = parameters->barrier;
    pthread_mutex_t* mutex = parameters->mutex;
	int i, j, r;

    r = pthread_mutex_lock(mutex);

    if(r != 0) {
        printf("Error when locking mutex\n");
        exit(-1);
    }

    if (numberToFind < array[end]) {

        if (array[end] < *upperBound) {
            *upperBound = array[end];
            *rightThread = thread_id;
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

    if (*rightThread == -1) {


        r = pthread_mutex_lock(mutex);

        if(r != 0) {
            printf("Error when locking mutex\n");
            exit(-1);
        }

        if (numberToFind == array[end]) {
            *upperBound = array[end];
            *rightThread = thread_id;
        }

        r = pthread_mutex_unlock(mutex);

        if(r != 0) {
            printf("Error when unlocking mutex\n");
            exit(-1);
        }
    }

    if (thread_id == *rightThread) {

        if (numberToFind == array[end]) {
            printf("Found %d in subarray %d\n", numberToFind, thread_id + 1);
            pthread_exit(NULL);
        }

        for (i = start; i < end; i++) {
            if (array[i] == numberToFind) {
                printf("Found %d in subarray %d\n", numberToFind, thread_id + 1);
                pthread_exit(NULL);
            }
        }
        printf("Number %d, not found\n", numberToFind);
    }

    if (thread_id == 0) {
        if (*rightThread == -1) {
            printf("Number %d, not found\n", numberToFind);
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
    int numberToFind = (int) strtol(argv[1], NULL, 10);

    
    struct coreParameters parameters[nr_threads];

    int array_size = 16;
    int array[] = {1, 1, 2, 3, 5, 5, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9};
    int upperBound = array[array_size - 1] + 1;
    int rightThread = -1;

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

        if (i == nr_threads - 1) {
            parameters[i].end = end - 1;
        }

        else {
             parameters[i].end = end;
        }

        parameters[i].threadID = i;
        parameters[i].numOfThreads = nr_threads;
        parameters[i].array_size = array_size;
        parameters[i].numberToFind = numberToFind;
        parameters[i].upperBound = &upperBound;
        parameters[i].rightThread = &rightThread;
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
