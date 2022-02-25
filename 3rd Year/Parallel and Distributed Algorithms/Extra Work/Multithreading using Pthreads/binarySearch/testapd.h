#include <stdio.h>
#include <pthread.h>

struct coreParameters {
	int start;
	int end;
	int array_size;
	int numberToFind;
	int *upperBound;
	int *rightThread;
	int numOfThreads;
	int threadID;
    int *array;
    pthread_barrier_t* barrier;
	pthread_mutex_t* mutex;
};