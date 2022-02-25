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
    int array_size = parameters->array_size;
    int *array = parameters->array;
    int numberToBroadcast = parameters->numberToBroadcast;
    pthread_barrier_t* barrier = parameters->barrier;
    pthread_mutex_t* mutex = parameters->mutex;

	
    int indxCur = thread_id;
    while(indxCur < array_size) {
        array[indxCur] = numberToBroadcast;
        indxCur +=nr_threads;
    }
    
    int r;
    r = pthread_barrier_wait(barrier);
    if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
        printf("Error when waiting for threads\n");
        exit(-1);
    }
    
    if(thread_id == 0){
        for(int i = 0; i < array_size; i++) {
            printf("%d ", array[i]);
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
    int numberToBroadcast = (int) strtol(argv[1], NULL, 10);

    
    struct coreParameters parameters[nr_threads];

    int array_size = 10;
    int array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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

	for (i = 0; i < nr_threads; i++) {
		
        // Calculating the start and end indexes for each subpart of the array

        parameters[i].threadID = i;
        parameters[i].numOfThreads = nr_threads;
        parameters[i].array_size = array_size;
        parameters[i].numberToBroadcast = numberToBroadcast;
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
