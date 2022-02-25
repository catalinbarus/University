#include <stdio.h>
#include <pthread.h>

struct coreParameters {
	int start;
	int end;
	int array_size;
	int numOfThreads;
	int threadID;
    int *initial_array;
    int *rank_array;
    int *sorted_array;
    pthread_barrier_t* barrier;
	pthread_mutex_t* mutex;
};