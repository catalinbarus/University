/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <cblas.h>

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	double *C = (double *) calloc(N * N, sizeof(double));

	if (C == NULL) {
		return (double*) -1;
	}

	double *D = (double *) calloc(N * N, sizeof(double));

	if (D == NULL) {
		return (double*) -1;
	}

	/* Calculez B x A */
	memcpy(C, B, N * N * sizeof(double));

	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit,
		N, N, 1.0, A, N, C, N);	

	/* Calculez C x A' */
	memcpy(D, C, N * N * sizeof(double));

	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit,
		N, N, 1.0, A, N, D, N);


	/* Mai adun la rezultat si B' x B */
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans,
		N, N, N, 1.0, B, N, B, N, 1.0, D, N);

	free(C);

	return D;
}
