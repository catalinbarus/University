#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int L; // latura matricei
int N; // numarul de elemente de sortat
int P;
int *v;
int *vQSort;
int **M;

pthread_barrier_t barrier;

/* Scalabilitate program */

// Procesorul pe care a fost rulat codul are 4 core-uri,
// deci vom analiza performanta folosind 4 thread-uri

// In urma rularii versiunii paralele am obtinut urmatorele rezultate:

/* catalin@MacBookPro-11:~/Desktop/APD/laboratoare/lab03$ time ./shear 100 4

real	0m0,007s
user	0m0,000s
sys	    0m0,013s

*/

// iar in urma rularii versiunii seriale am obtinut:

/*catalin@MacBookPro-11:~/Desktop/APD/laboratoare/lab03$ time ./shear 100 4

real	0m0,010s
user	0m0,010s
sys	    0m0,000s

*/

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

void display_matrix(int **M) {
	int i, j;
	int display_width = 2 + log10(N);

	for (i = 0; i < L; i++) {
		for (j = 0; j < L; j++) {
			printf("%*i", display_width, M[i][j]);
		}
		printf("\n");
	}
}

void copy_matrix_in_vector(int *v, int **M) {
	int i, j;
	for (i = 0; i < L; i++) {
		if (i % 2 == 0) {
			for (j = 0; j < L; j++) {
				v[i * L + j] = M[i][j];
			}
		} else {
			for (j = L; j > 0; j--) {
				v[i * L + (L - j)] = M[i][j-1];
			}
		}
	}
}

int cmp(const void *a, const void *b) {
	int A = *(int*)a;
	int B = *(int*)b;
	return A - B;
}

int cmpdesc(const void *a, const void *b) {
	int A = *(int*)a;
	int B = *(int*)b;
	return B - A;
}

void get_args(int argc, char **argv)
{
	if(argc < 3) {
		printf("Numar insuficient de parametri: ./shear L P (L = latura matricei)\n");
		exit(1);
	}

	L = atoi(argv[1]);
	N = L * L;
	P = atoi(argv[2]);
}

void init()
{
	int i, j;
	v = malloc(sizeof(int) * N);
	vQSort = malloc(sizeof(int) * N);
	M = malloc(sizeof(int*) * L);

	if (v == NULL || vQSort == NULL || M == NULL) {
		printf("Eroare la malloc!");
		exit(1);
	}

	for (i = 0; i < L; i++) {
		M[i] = malloc(sizeof(int) * L);
	}

	srand(42);

	for (i = 0; i < L; i++) {
		for (j = 0; j < L; j++) {
			M[i][j] = rand() % N;
		}
	}
}

void print()
{
	printf("M:\n");
	display_matrix(M);

	copy_matrix_in_vector(v, M);
	printf("v:\n");
	display_vector(v);
	printf("vQSort:\n");
	display_vector(vQSort);
	compare_vectors(v, vQSort);	
}

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;

	// implementati aici shear sort paralel

	for(int k = 0; k < log(N) + 1; k++) {
        for(int i = thread_id; i < L; i += P) {
            if (i % 2) {
                qsort(M[i], L, sizeof(int), cmpdesc);
            } else {
                qsort(M[i], L, sizeof(int), cmp);
            }
        }

        
        pthread_barrier_wait(&barrier);

        for (int i = thread_id; i < L; i += P) {
            int aux[L];
            for (int j = 0; j < L; j++) {
                aux[j] = M[j][i];
            }
            
            qsort(aux, L, sizeof(int), cmp);

            for (int j = 0; j < L; j++) {
                M[j][i] = aux[j];
            }
        }

        
        pthread_barrier_wait(&barrier);
    }


	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	get_args(argc, argv);
	init();

	int i, r;
	//int j, k, aux[L];
	pthread_t tid[P];
	int thread_id[P];

	// Initializam bariera
	r = pthread_barrier_init(&barrier, NULL, P);

	if(r != 0) {
		printf("Eroare la initializarea barierei\n");
		exit(-1);
	}

	// se sorteaza etalonul
	copy_matrix_in_vector(vQSort, M);
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

	// shear sort clasic - trebuie paralelizat
	/*for (k = 0; k < log(N) + 1; k++) {
		// se sorteaza liniile pare crescator
		// se sorteaza liniile impare descrescator
		for (i = 0; i < L; i++) {
			if (i % 2) {
				qsort(M[i], L, sizeof(int), cmpdesc);
			} else {
				qsort(M[i], L, sizeof(int), cmp);
			}
		}

		// se sorteaza coloanele descrescator
		for (i = 0; i < L; i++) {
			for (j = 0; j < L; j++) {
				aux[j] = M[j][i];
			}

			qsort(aux, L, sizeof(int), cmp);

			for (j = 0; j < L; j++) {
				M[j][i] = aux[j];
			}
		}
	}*/

	// se afiseaza matricea
	// se afiseaza vectorul etalon
	// se afiseaza matricea curenta sub forma de vector
	// se compara cele doua
	print();

	free(v);
	free(vQSort);
	for (i = 0; i < L; i++) {
		free(M[i]);
	}
	free(M);

	// Dezalocam bariera
	r = pthread_barrier_destroy(&barrier);

	if(r != 0) {
		printf("Eroare la distrugerea barierei\n");
		exit(-1);
	}

	return 0;
}
