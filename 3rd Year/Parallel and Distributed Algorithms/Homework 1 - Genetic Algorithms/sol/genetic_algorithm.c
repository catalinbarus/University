#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "genetic_algorithm.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))

// Parsing the input, plus the number of threads
int read_input(sack_object **objects, int *object_count, int *sack_capacity, int *generations_count, int *numOfThreads, int argc, char *argv[])
{
	FILE *fp;

	if (argc < 4) {
		fprintf(stderr, "Usage:\n\t./tema1 in_file generations_count num_of_threads\n");
		return 0;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		return 0;
	}

	if (fscanf(fp, "%d %d", object_count, sack_capacity) < 2) {
		fclose(fp);
		return 0;
	}

	if (*object_count % 10) {
		fclose(fp);
		return 0;
	}

	sack_object *tmp_objects = (sack_object *) calloc(*object_count, sizeof(sack_object));

	for (int i = 0; i < *object_count; ++i) {
		if (fscanf(fp, "%d %d", &tmp_objects[i].profit, &tmp_objects[i].weight) < 2) {
			free(objects);
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);

	*generations_count = (int) strtol(argv[2], NULL, 10);
	
	if (*generations_count == 0) {
		free(tmp_objects);

		return 0;
	}

	*numOfThreads = (int) strtol(argv[3], NULL, 10);

	*objects = tmp_objects;

	return 1;
}

void print_objects(const sack_object *objects, int object_count)
{
	for (int i = 0; i < object_count; ++i) {
		printf("%d %d\n", objects[i].weight, objects[i].profit);
	}
}

void print_generation(const individual *generation, int limit)
{
	for (int i = 0; i < limit; ++i) {
		for (int j = 0; j < generation[i].chromosome_length; ++j) {
			printf("%d ", generation[i].chromosomes[j]);
		}

		printf("\n%d - %d\n", i, generation[i].fitness);
	}
}

void print_best_fitness(const individual *generation)
{
	printf("%d\n", generation[0].fitness);
}

void compute_fitness_function(const sack_object *objects, individual *generation, int object_count, int sack_capacity, int start, int end)
{
	int weight;
	int profit;

	for (int i = start; i < end; ++i) {
		weight = 0;
		profit = 0;

		for (int j = 0; j < generation[i].chromosome_length; ++j) {
			if (generation[i].chromosomes[j]) {
				weight += objects[j].weight;
				profit += objects[j].profit;
			}
		}

		generation[i].fitness = (weight <= sack_capacity) ? profit : 0;
	}
}

int cmpfunc(const void *a, const void *b)
{
	int i;
	individual *first = (individual *) a;
	individual *second = (individual *) b;

	int res = second->fitness - first->fitness; // decreasing by fitness
	if (res == 0) {
		int first_count = 0, second_count = 0;

		for (i = 0; i < first->chromosome_length && i < second->chromosome_length; ++i) {
			first_count += first->chromosomes[i];
			second_count += second->chromosomes[i];
		}

		res = first_count - second_count; // increasing by number of objects in the sack
		if (res == 0) {
			return second->index - first->index;
		}
	}

	return res;
}

void mutate_bit_string_1(const individual *ind, int generation_index)
{
	int i, mutation_size;
	int step = 1 + generation_index % (ind->chromosome_length - 2);

	if (ind->index % 2 == 0) {
		// for even-indexed individuals, mutate the first 40% chromosomes by a given step
		mutation_size = ind->chromosome_length * 4 / 10;
		for (i = 0; i < mutation_size; i += step) {
			ind->chromosomes[i] = 1 - ind->chromosomes[i];
		}
	} else {
		// for even-indexed individuals, mutate the last 80% chromosomes by a given step
		mutation_size = ind->chromosome_length * 8 / 10;
		for (i = ind->chromosome_length - mutation_size; i < ind->chromosome_length; i += step) {
			ind->chromosomes[i] = 1 - ind->chromosomes[i];
		}
	}
}

void mutate_bit_string_2(const individual *ind, int generation_index)
{
	int step = 1 + generation_index % (ind->chromosome_length - 2);

	// mutate all chromosomes by a given step
	for (int i = 0; i < ind->chromosome_length; i += step) {
		ind->chromosomes[i] = 1 - ind->chromosomes[i];
	}
}

void crossover(individual *parent1, individual *child1, int generation_index)
{
	individual *parent2 = parent1 + 1;
	individual *child2 = child1 + 1;
	int count = 1 + generation_index % parent1->chromosome_length;

	memcpy(child1->chromosomes, parent1->chromosomes, count * sizeof(int));
	memcpy(child1->chromosomes + count, parent2->chromosomes + count, (parent1->chromosome_length - count) * sizeof(int));

	memcpy(child2->chromosomes, parent2->chromosomes, count * sizeof(int));
	memcpy(child2->chromosomes + count, parent1->chromosomes + count, (parent1->chromosome_length - count) * sizeof(int));
}

void copy_individual(const individual *from, const individual *to)
{
	memcpy(to->chromosomes, from->chromosomes, from->chromosome_length * sizeof(int));
}

void free_generation(individual *generation)
{
	int i;

	for (i = 0; i < generation->chromosome_length; ++i) {
		free(generation[i].chromosomes);
		generation[i].chromosomes = NULL;
		generation[i].fitness = 0;
	}
}

// Merge function, used for merging two parts of an array
void merge(individual *current_generation, int low, int mid, int high)
{
	individual left[mid - low + 1];
	individual right[high - mid]; 
 
    // Computing size for left and right parts
    int n1 = mid - low + 1;
	int n2 = high - mid;
	int i, j;
 
    // Storing the values for the left part of the array
    for (i = 0; i < n1; i++) {
        left[i] = current_generation[i + low];
	}
 
    // Storing the values for the right part of the array
    for (i = 0; i < n2; i++) {
        right[i] = current_generation[i + mid + 1];
	}
 
    int k = low;
    i = j = 0;
 
    // Merge according to the conditions imposed by cmpfunc
    while (i < n1 && j < n2) {

        if (cmpfunc(&left[i], &right[j]) < 0) {
            current_generation[k++] = left[i++];
		}

        else {
            current_generation[k++] = right[j++];
		}
    }
 
    // Insert the remaining values from the left part of the array
    while (i < n1) {
        current_generation[k++] = left[i++];
    }
 
    // Insert the remaining values from the right part of the array
    while (j < n2) {
        current_generation[k++] = right[j++];
    }
}
 
// The actual merge sort function
void merge_sort(individual *current_generation, int low, int high)
{
    int mid = low + (high - low) / 2;
    if (low < high) {
 
        // Computing first half of the array
        merge_sort(current_generation, low, mid);
 
        // Computing second half of the array
        merge_sort(current_generation, mid + 1, high);
 
        // Merging the two halves of the array
        merge(current_generation, low, mid, high);
    }
}
 
void* run_genetic_algorithm(void* arg)
{
	int count, cursor, r, start, end;

	// Restoring parameters from struct
	struct generationSpecifications* genSpecs = (struct generationSpecifications*) arg;
	start = genSpecs->start;
	end = genSpecs->end;
	const sack_object* objects = genSpecs->objects;
	individual *current_generation = genSpecs->current_generation;
	individual *next_generation = genSpecs->next_generation;
	individual *tmp = genSpecs->tmp;
	int object_count = genSpecs->object_count;
	int	generations_count = genSpecs->generations_count;
	int	sack_capacity = genSpecs->sack_capacity;
	int	numOfThreads = genSpecs->numOfThreads;
	int	threadID = genSpecs->threadID;
	pthread_barrier_t* barrier = genSpecs->barrier;
	pthread_mutex_t* mutex = genSpecs->mutex;
	
	// The first for used to initialize fields, parallelised
	for (int i = start; i < end; i++) {
		current_generation[i].fitness = 0;
		current_generation[i].chromosomes = (int*) calloc(object_count, sizeof(int));
		current_generation[i].chromosomes[i] = 1;
		current_generation[i].index = i;
		current_generation[i].chromosome_length = object_count;

		next_generation[i].fitness = 0;
		next_generation[i].chromosomes = (int*) calloc(object_count, sizeof(int));
		next_generation[i].index = i;
		next_generation[i].chromosome_length = object_count;
	}
	
	// Wait for all threads to finish the initialization
	r = pthread_barrier_wait(barrier);
	if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
        printf("Error when waiting for threads\n");
        exit(-1);
    }

	// Lock the computing of the start and end indexes used for
	// the merge sort algorithm so that only one thread can pass
	// at a time
	r = pthread_mutex_lock(mutex);

	if(r != 0) {
		printf("Error when locking mutex\n");
		exit(-1);
	}

	int low = (threadID) * (object_count / numOfThreads);
    int high = (threadID + 1) * (object_count / numOfThreads) - 1;

	r = pthread_mutex_unlock(mutex);

	if(r != 0) {
		printf("Error when unlocking mutex\n");
		exit(-1);
	}

	// Iterate for each generation
	for (int k = 0; k < generations_count; ++k) {

		// Wait for all threads to reach next iteration
		r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}

		cursor = 0;

		// Compute fitness and sort by it (parallelised using start and end indexes for each thread)
		compute_fitness_function(objects, current_generation, object_count, sack_capacity, start, end);

		r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}

		// Compute mid for merge sort
		int mid = low + (high - low) / 2;

		if (low < high) {
			merge_sort(current_generation, low, mid);
			merge_sort(current_generation, mid + 1, high);
			merge(current_generation, low, mid, high);
		}

		// Wait for all threads to sort their part of the array
		r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}

		// Check the number of threads available, so we know how to merge the subarrays
		if (numOfThreads == 2 && threadID == 0) {
			merge(current_generation, 0, object_count / 2 - 1, object_count - 1);
		}

		if (numOfThreads == 3 && threadID == 0) {
			merge(current_generation, 0, object_count / 3 - 1, object_count * 2 / 3 - 1);
			merge(current_generation, 0, object_count * 2 / 3 - 1, object_count - 1);
		}

		if (numOfThreads == 4 && threadID == 0) {
			merge(current_generation, 0, (object_count / 2 - 1) / 2, object_count/ 2 - 1);
			merge(current_generation, object_count / 2, object_count/2 + (object_count-1-object_count/2)/2, object_count - 1);
			merge(current_generation, 0, (object_count - 1)/2, object_count - 1);
		}

		// Wait for all threads to finish the merging process
		r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}
		
		// Keep first 30% children (elite children selection)
		count = object_count * 3 / 10;

		// Indexes used to parallelise iterations of size "count"
		int startCount = threadID * (double)count / numOfThreads;
		int endCount = min((threadID + 1) * (double)count / numOfThreads, count);

		// Parallelised according to startCount and endCount values
		for (int i = startCount; i < endCount; ++i) {
			copy_individual(current_generation + i, next_generation + i);
		}
		cursor = count;

		// Wait for all threads to finish computations
		r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}

		// mutate first 20% children with the first version of bit string mutation
		count = object_count * 2 / 10;

		
		startCount = threadID * (double)count / numOfThreads;
		endCount = min((threadID + 1) * (double)count / numOfThreads, count);

		// Parallelised according to startCount and endCount values
		for (int i = startCount; i < endCount; ++i) {
			copy_individual(current_generation + i, next_generation + cursor + i);
			mutate_bit_string_1(next_generation + cursor + i, k);
		}
		cursor += count;

		// Wait for all threads to finish computations
		r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}

		// mutate next 20% children with the second version of bit string mutation
		count = object_count * 2 / 10;

		startCount = threadID * (double)count / numOfThreads;
		endCount = min((threadID + 1) * (double)count / numOfThreads, count);

		// Parallelised according to startCount and endCount values
		for (int i = startCount; i < endCount; ++i) {
			copy_individual(current_generation + i + count, next_generation + cursor + i);
			mutate_bit_string_2(next_generation + cursor + i, k);
		}
		cursor += count;
		
		// Wait for all threads to finish computations
		r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}

		// Crossover first 30% parents with one-point crossover
		// (if there is an odd number of parents, the last one is kept as such)
		count = object_count * 3 / 10;

		if (threadID == 0) {

			if (count % 2 == 1) {
				copy_individual(current_generation + object_count - 1, next_generation + cursor + count - 1);
				count--;
			}

			for (int i = 0; i < count; i += 2) {
				crossover(current_generation + i, next_generation + cursor + i, k);
			}
		}
		
		// Wait for all threads to finish computations
		r = pthread_barrier_wait(barrier);
		if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
			printf("Error when waiting for threads\n");
			exit(-1);
		}

		// Switch to new generation
		tmp = current_generation;
		current_generation = next_generation;
		next_generation = tmp;

		for (int i = 0; i < object_count; ++i) {
			current_generation[i].index = i;
		}

		// Use one thread only to display the results
		if (k % 5 == 0 && threadID == 0) {
			print_best_fitness(current_generation);
		}
	}

	// Compute fitness and sort by it (parallelised using start and end indexes for each thread)
	compute_fitness_function(objects, current_generation, object_count, sack_capacity, 0, object_count);

	// Wait for all threads to finish computations
	r = pthread_barrier_wait(barrier);
	if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
        printf("Error when waiting for threads\n");
        exit(-1);
    }

	// MergeSort the subarrays once more
	int mid = low + (high - low) / 2;

	if (low < high) {
		merge_sort(current_generation, low, mid);
		merge_sort(current_generation, mid + 1, high);
		merge(current_generation, low, mid, high);
	}

	// Wait for all threads to sort their part of the array
	r = pthread_barrier_wait(barrier);
	if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
		printf("Error when waiting for threads\n");
		exit(-1);
	}

	// Once again, check the number of threads available, 
	// so we know how to merge the subarrays
	if (numOfThreads == 2 && threadID == 0) {
		merge(current_generation, 0, object_count / 2 - 1, object_count - 1);
	}

	if (numOfThreads == 3 && threadID == 0) {
		merge(current_generation, 0, object_count / 3 - 1, object_count * 2 / 3 - 1);
		merge(current_generation, 0, object_count * 2 / 3 - 1, object_count - 1);
	}

	if (numOfThreads == 4 && threadID == 0) {
		merge(current_generation, 0, (object_count / 2 - 1) / 2, object_count/ 2 - 1);
		merge(current_generation, object_count / 2, object_count/2 + (object_count-1-object_count/2)/2, object_count - 1);
		merge(current_generation, 0, (object_count - 1)/2, object_count - 1);
	}

	// Wait for all threads to merge their part of the subarray
	r = pthread_barrier_wait(barrier);
	if (r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0) {
		printf("Error when waiting for threads\n");
		exit(-1);
	}

	// Use one thread only to display the results
	if (threadID == 0) {
		print_best_fitness(current_generation);
	}

 	pthread_exit(NULL);
}