#include <stdio.h>
#include <pthread.h>

struct coreParameters {
	int start;
	int end;
	int array_size;
	int numberToFind;
	int numOfThreads;
	int threadID;
    int *array;
	int *output_array;
	int *temp;
	int *bit_array;
    pthread_barrier_t* barrier;
	pthread_mutex_t* mutex;
};