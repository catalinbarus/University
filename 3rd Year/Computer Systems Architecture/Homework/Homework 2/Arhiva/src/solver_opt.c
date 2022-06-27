/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
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

	register int i, j, k;
	
	/* Calculez B x A */
	for (i = 0; i < N; i++) {

		/* Retinem linia i din matricea C */
		register double *c_ith_row = C + i * N;

		/* Retinem linia i din matricea A */
		register double *b_ith_row = B + i * N;

		for (j = 0; j < N; j++) {

			/* Calculam suma pentru linia curenta */
			register double s = 0;
			register double *b_row = b_ith_row;

			/* Retinem coloana din din matricea A */
			register double *a_jth_col = A + j;
		
			for (k = 0; k <= j; k++) {
				s += *b_row * *a_jth_col;
				a_jth_col += N;
				b_row++;
			}

			*c_ith_row = s;
			c_ith_row++;
		}
	}

	/* Calculez C x A' */
	for (i = 0; i < N; i++) {

		/* Retinem linia i din matricea D */
		register double *d_ith_row = D + i * N;

		/* Retinem linia i din matricea C */
		register double *c_ith_row = C + i * N;

		for (j = 0; j < N; j++) {

			/* Calculam suma pentru linia curenta */
			register double s = 0;
			register double *c_row = c_ith_row;

			/* Sarim peste elementele din C care 
			se vor inmulti cu zerouri din A */
			c_row += j;

			/* Retinem linia j si coloana j din matricea A' */
			register double *a_trans = A + j * N + j;

			for (k = j; k < N; k++) {
				s += *c_row * *a_trans;
				c_row++;
				a_trans++;
			}

			*d_ith_row = s;
			d_ith_row++;
		}
	}

	/* Mai adun la rezultat si B' x B */
	for (i = 0; i < N; i++) {

		/* Retinem linia i din matricea D */
		register double *d_ith_row = D + i * N;

		/* Retinem coloana i din matricea B */
		register double *b_trans_ith_col = B + i;
		
		for (j = 0; j < N; j++) {

			/* Calculam suma pentru linia curenta */
			register double s = 0;
			register double *b_trans = b_trans_ith_col;

			/* Retinem coloana j din matricea B */
			register double *b_jth_col = B + j;

			for (k = 0; k < N; k++) {

				s += *b_trans * *b_jth_col;
				b_trans += N;
				b_jth_col += N;
			}

			*d_ith_row = *d_ith_row + s;
			d_ith_row++;
		}
	}

	free(C);
	
	return D;	
}
