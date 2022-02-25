#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "testapd.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))

// Merge function, used for merging two parts of an array
void merge(int *array, int low, int mid, int high)
{
	int left[mid - low + 1];
	int right[high - mid]; 
 
    // Computing size for left and right parts
    int n1 = mid - low + 1;
	int n2 = high - mid;
	int i, j;
 
    // Storing the values for the left part of the array
    for (i = 0; i < n1; i++) {
        left[i] = array[i + low];
	}
 
    // Storing the values for the right part of the array
    for (i = 0; i < n2; i++) {
        right[i] = array[i + mid + 1];
	}
 
    int k = low;
    i = j = 0;
 
    // Merge according to the conditions imposed by cmpfunc
    while (i < n1 && j < n2) {

        if (left[i] <= right[j]) {
            array[k++] = left[i++];
		}

        else {
            array[k++] = right[j++];
		}
    }
 
    // Insert the remaining values from the left part of the array
    while (i < n1) {
        array[k++] = left[i++];
    }
 
    // Insert the remaining values from the right part of the array
    while (j < n2) {
        array[k++] = right[j++];
    }
}
 
// The actual merge sort function
void merge_sort(int *array, int low, int high)
{
    int mid = low + (high - low) / 2;
    if (low < high) {
 
        // Computing first half of the array
        merge_sort(array, low, mid);
 
        // Computing second half of the array
        merge_sort(array, mid + 1, high);
 
        // Merging the two halves of the array
        merge(array, low, mid, high);
    }
}

void *thread_function(void *arg)
{
	struct coreParameters* parameters = (struct coreParameters*) arg;

    int thread_id = parameters->threadID;
    int nr_threads = parameters->numOfThreads;
    int start = parameters->start;
    int end = parameters->end;
    int array_size = parameters->array_size;
    int *array = parameters->array;
    int *output_array = parameters->output_array;
    int *temp = parameters->temp;
    pthread_barrier_t* barrier = parameters->barrier;
    pthread_mutex_t* mutex = parameters->mutex;
	int i, j, r;

    int low = (thread_id) * (array_size / nr_threads);
    int high = (thread_id + 1) * (array_size / nr_threads) - 1;
    int mid = low + (high - low) / 2;

    if (low < high) {
        merge_sort(array, low, mid);
        merge_sort(array, mid + 1, high);
        merge(array, low, mid, high);
    }

    // Wait for all threads to sort their part of the array
    r = pthread_barrier_wait(barrier);
    if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
        printf("Error when waiting for threads\n");
        exit(-1);
    }

    // Check the number of threads available, so we know how to merge the subarrays
    if (nr_threads == 2 && thread_id == 0) {
        merge(array, 0, array_size / 2 - 1, array_size - 1);
    }

    if (nr_threads == 3 && thread_id == 0) {
        merge(array, 0, array_size / 3 - 1, array_size * 2 / 3 - 1);
        merge(array, 0, array_size * 2 / 3 - 1, array_size - 1);
    }

    if (nr_threads == 4 && thread_id == 0) {
        merge(array, 0, (array_size / 2 - 1) / 2, array_size/ 2 - 1);
        merge(array, array_size / 2, array_size/2 + (array_size-1-array_size/2)/2, array_size - 1);
        merge(array, 0, (array_size - 1)/2, array_size - 1);
    }

    // Wait for all threads to finish the merging process
    r = pthread_barrier_wait(barrier);
    if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
        printf("Error when waiting for threads\n");
        exit(-1);
    }

    if (thread_id == 0) {
        for (i = 0; i < array_size; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
		fprintf(stderr, "Usage:\n\t./testapd number_to_find number_of_threads\n");
		return 0;
	}

    // Declaram bariera
    pthread_barrier_t barrier;

    // Declaram mutex
    pthread_mutex_t mutex;

    int i, j, r;
    int nr_threads = (int) strtol(argv[1], NULL, 10);
   
    struct coreParameters parameters[nr_threads];

    int array_size = 9;
    int array[] = {420, 4, 16, 10, 16, 14, 2, 8, 7};
    int output_array[8];
    int temp[8];

    for (i = 0; i < array_size; i++) {
        output_array[i] = 0;
        temp[i] = 0;
    }

    output_array[0] = array[0];

    /*for (i = 1; i < array_size; i++) {
        output_array[i] = array[i] + output_array[i - 1];
    }*/

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
        parameters[i].end = end;
        parameters[i].threadID = i;
        parameters[i].numOfThreads = nr_threads;
        parameters[i].array_size = array_size;
        parameters[i].array = array;
        parameters[i].output_array = output_array;
        parameters[i].temp = temp;
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
