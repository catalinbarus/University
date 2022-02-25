#include <stdio.h>
#include <pthread.h>

struct coreParameters {
	int start;
	int end;
	int array_size;
	int maxNumber;
	int numOfThreads;
	int threadID;
	int *sum_array;
    int *array;
    pthread_barrier_t* barrier;
	pthread_mutex_t* mutex;
};