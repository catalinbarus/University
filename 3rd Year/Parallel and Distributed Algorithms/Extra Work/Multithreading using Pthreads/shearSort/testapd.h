#include <stdio.h>
#include <pthread.h>

struct coreParameters {
	int start;
	int end;
	int array_size;
	int matrixLen;
	int numOfThreads;
	int threadID;
	int **matrix;
    int *array;
	int *output_array;
	int *temp;
    pthread_barrier_t* barrier;
	pthread_mutex_t* mutex;
};