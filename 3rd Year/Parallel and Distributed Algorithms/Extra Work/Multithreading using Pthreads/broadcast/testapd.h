#include <stdio.h>
#include <pthread.h>

struct coreParameters {
	int array_size;
	int numOfThreads;
	int threadID;
	int numberToBroadcast;
    int *array;
    pthread_barrier_t* barrier;
	pthread_mutex_t* mutex;
};