#include <stdlib.h>
#include "genetic_algorithm.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))

int main(int argc, char *argv[]) {

	// Declaring barrier
	pthread_barrier_t barrier;

	// Declaring mutex
	pthread_mutex_t mutex;

	int r;
	
	// array with all the objects that can be placed in the sack
	sack_object *objects = NULL;

	// number of objects
	int object_count = 0;

	// maximum weight that can be carried in the sack
	int sack_capacity = 0;

	// number of generations
	int generations_count = 0;

	// number of threads
	int numOfThreads = 0;

	// Read input, plus the number of threads available
	if (!read_input(&objects, &object_count, &sack_capacity, &generations_count, &numOfThreads, argc, argv)) {
		return 0;
	}

	// Array used by the threads
	pthread_t threads[numOfThreads];
	long id;
    void *status;

	// Struct used for storing the parameters of the thread function
	struct generationSpecifications genSpecs[numOfThreads];

	// Arrays used for the current and next generations
	individual *current_generation = (individual*) calloc(object_count, sizeof(individual));
	individual *next_generation = (individual*) calloc(object_count, sizeof(individual));
	individual *tmp = NULL;
	
	// Initializing the barrier
    r = pthread_barrier_init(&barrier, NULL, numOfThreads);
    if(r != 0) {
        printf("Error when creating barrier\n");
        exit(-1);
    }

	// Initializing the mutex
	r = pthread_mutex_init(&mutex, NULL);
	if(r != 0) {
        printf("Error when creating mutex\n");
        exit(-1);
    }
	
	int start, end;

	for (int i = 0; i < numOfThreads; i++) {

		// Calculating the start and end indexes for each subpart of the array
		start = i * (double)object_count / numOfThreads;
		end = min((i + 1) * (double)object_count / numOfThreads, object_count);

		// Storing all the parameters from the sequential version of the
		// "run_genetic_algorithm" function (as well as additional ones)
		genSpecs[i].start = start;
		genSpecs[i].end = end;
		genSpecs[i].objects = objects;
		genSpecs[i].current_generation = current_generation;
		genSpecs[i].next_generation = next_generation;
		genSpecs[i].tmp = tmp;
		genSpecs[i].object_count = object_count;
		genSpecs[i].generations_count = generations_count;
		genSpecs[i].sack_capacity = sack_capacity;
		genSpecs[i].numOfThreads = numOfThreads;
		genSpecs[i].threadID = i;
		genSpecs[i].barrier = &barrier;
		genSpecs[i].mutex = &mutex;

		// Split the exectution into multiple threads
        r = pthread_create(&threads[i], NULL, run_genetic_algorithm, (void *) &genSpecs[i]);

        if (r) {
            printf("Error when creating thread: %d\n", i);
            exit(-1);
        }
	} 

	// Joining the threads
	for (id = 0; id < numOfThreads; id++) {
        r = pthread_join(threads[id], &status);
 
        if (r) {
            printf("Error at trying to join thread: %ld\n", id);
            exit(-1);
        }
    }

	// Free the barrier
    r = pthread_barrier_destroy(&barrier);
    if(r != 0) {
        printf("Error when destroying barrier\n");
        exit(-1);
    }

	// Free the mutex
	r= pthread_mutex_destroy(&mutex);
	if(r != 0) {
        printf("Error when destroying mutex\n");
        exit(-1);
    }

	free(objects);

	return 0;
}
