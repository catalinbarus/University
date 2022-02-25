#include <stdio.h>
#include <pthread.h>

struct coreParameters {
	int start;
	int end;
	int matrixLen;
	int power;
	int numOfThreads;
	int threadID;
	long **matrix;
	long **matrix_copy;
	long **result;
    pthread_barrier_t* barrier;
	pthread_mutex_t* mutex;
};