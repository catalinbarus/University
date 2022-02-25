#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N;
int P;
int *v;
int *vQSort;
int *vNew;

pthread_barrier_t barrier;

/* Scalabilitate program */

// Procesorul pe care a fost rulat codul are 4 core-uri,
// deci vom analiza performanta folosind 4 thread-uri

// In urma rularii versiunii paralele am obtinut urmatorele rezultate:

/* catalin@MacBookPro-11:~/Desktop/APD/laboratoare/lab03$ time ./merge 128 4

real	0m0,003s
user	0m0,003s
sys	    0m0,000s


*/

// iar in urma rularii versiunii seriale am obtinut:

/*catalin@MacBookPro-11:~/Desktop/APD/laboratoare/lab03$ time ./merge 128 4

real	0m0,006s
user	0m0,006s
sys	    0m0,000s

*/

void merge(int *source, int start, int mid, int end, int *destination) {
	int iA = start;
	int iB = mid;
	int i;

	for (i = start; i < end; i++) {
		if (end == iB || (iA < mid && source[iA] <= source[iB])) {
			destination[i] = source[iA];
			iA++;
		} else {
			destination[i] = source[iB];
			iB++;
		}
	}
}

void compare_vectors(int *a, int *b) {
	int i;

	for (i = 0; i < N; i++) {
		if (a[i] != b[i]) {
			printf("Sortare incorecta\n");
			return;
		}
	}

	printf("Sortare corecta\n");
}

void display_vector(int *v) {
	int i;
	int display_width = 2 + log10(N);

	for (i = 0; i < N; i++) {
		printf("%*i", display_width, v[i]);
	}

	printf("\n");
}

int cmp(const void *a, const void *b) {
	int A = *(int*)a;
	int B = *(int*)b;
	return A - B;
}

int is_power_of_two(int n)
{
	if (n == 0) {
		return 0;
	}

	return (ceil(log2(n)) == floor(log2(n)));
}

void get_args(int argc, char **argv)
{
	if(argc < 3) {
		printf("Numar insuficient de parametri: ./merge N P (N trebuie sa fie putere a lui 2)\n");
		exit(1);
	}

	N = atoi(argv[1]);
	if (!is_power_of_two(N)) {
		printf("N trebuie sa fie putere a lui 2\n");
		exit(1);
	}

	P = atoi(argv[2]);
}

void init()
{
	int i;
	v = malloc(sizeof(int) * N);
	vQSort = malloc(sizeof(int) * N);
	vNew = malloc(sizeof(int) * N);

	if (v == NULL || vQSort == NULL || vNew == NULL) {
		printf("Eroare la malloc!");
		exit(1);
	}

	srand(42);

	for (i = 0; i < N; i++)
		v[i] = rand() % N;
}


void print()
{
	printf("v:\n");
	display_vector(v);
	printf("vQSort:\n");
	display_vector(vQSort);
	compare_vectors(v, vQSort);
}

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;

	int width, *aux;
	for (width = 1; width < N; width = 2 * width) { 
		for (int i = 2 * thread_id * width; i < N; i += 2 * width * P) {
			merge(v, i, i + width, i + 2 * width, vNew);
		}

        // Asteptam bariera
        pthread_barrier_wait(&barrier);
		
        // Ne asiguram ca se executa doar pe primul thread
        if(thread_id == 0) {
            aux = v;
            v = vNew;
            vNew = aux;
        }
        
        // Asteptam bariera
        pthread_barrier_wait(&barrier);
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	get_args(argc, argv);
	init();

	int i, r;
	int thread_id[P];
	pthread_t tid[P];

	// Initializam bariera
	r = pthread_barrier_init(&barrier, NULL, P);

	if(r != 0) {
		printf("Eroare la initializarea barierei\n");
		exit(-1);
	}

	// se sorteaza vectorul etalon
	for (i = 0; i < N; i++)
		vQSort[i] = v[i];
	qsort(vQSort, N, sizeof(int), cmp);

	// se creeaza thread-urile
	for (i = 0; i < P; i++) {
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

	// se asteapta thread-urile
	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	// merge sort clasic - trebuie paralelizat
	/*int width, *aux;
	for (width = 1; width < N; width = 2 * width) {
		for (i = 0; i < N; i = i + 2 * width) {
			merge(v, i, i + width, i + 2 * width, vNew);
		}

		aux = v;
		v = vNew;
		vNew = aux;
	}*/

	print();

	free(v);
	free(vQSort);
	free(vNew);

	// Dezalocam bariera
	r = pthread_barrier_destroy(&barrier);

	if(r != 0) {
		printf("Eroare la distrugerea barierei\n");
		exit(-1);
	}

	return 0;
}
