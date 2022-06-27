/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	double *C = (double *) calloc(N * N, sizeof(double));

	if (C == NULL) {
		return (double*) -1;
	}
	
	double *D = (double *) calloc(N * N, sizeof(double));

	if (D == NULL) {
		return (double*) -1;
	}

	int i, j, k;
	
	/* Calculez B x A */
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k <= j; k++) {
				C[i * N + j] += B[i * N + k] * A[k * N + j];
			}
		}
	}

	/* Calculez C * A' */
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = j; k < N; k++) {
				D[i * N + j] += C[i * N + k] * A[j * N + k];
			}
		}
	}

	/* Mai adun la rezultat si B' x B */
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < N; k++) {
				D[i * N + j] += B[k * N + i] * B[k * N + j];
			}
		}
	}
	
	free(C);

	return D;
}
