#include <stdio.h>
#include <stdlib.h>


int power(int x, unsigned int y)
{
    if (y == 0)
        return 1;
    else if (y%2 == 0)
        return power(x, y/2)*power(x, y/2);
    else
        return x*power(x, y/2)*power(x, y/2);
}

void showPermutations(int size, int s[]) {

	for (int i = 1; i <= size; i++) {
		printf("%d ", s[i]);
	}
	printf("\n");
}

void genPermutations(int size, int k, int s[], int u[]) {

	if (k == (size + 1)) {
		showPermutations(size, s);
	} else {

		for (s[k] = 1; s[k] <= size; s[k]++) {

			if (u[s[k]] == 0) {
				u[s[k]] = 1;
				genPermutations(size, k + 1, s, u);
				u[s[k]] = 0;
			}
		}
	}
}

void genTable(int size, int s[]) {

	for (int i = 1; i <= size; i++) {

		for (int j = 1; j <= size; j++) {

			if (j == s[i]) {

				printf("D ");
			} 
			else {
				printf("* ");
			}
			
		}
		printf("\n");
	}
	printf("\n");
}

int valid(int k, int s[]) {

	for (int i = 1; i < k; i++) {

		if (s[k] == s[i] || (k - i) == abs(s[k] - s[i])) {
			return 0;
		}
	}
	return 1;
}

void genQueens(int size, int k, int s[]) {

	if (k == (size + 1)) {

		genTable(size, s);
	}

	else {

		for (s[k] = 1; s[k] <= size; s[k]++) {

			if (valid(k, s) == 1) {

				genQueens(size, k + 1, s);
			}
		}
	}
}

void genSubsets(int v[], int n) {

	int subset_size = power(2, n);

	for (int i = 0; i < subset_size; i++) {

		int subset[n];
		for (int j = 0; j < n; j++) {

			if ((i & (1 << j)) != 0) {
                subset[j] = v[j];
			}
		}

		for (int j = 0; j < n; j++) {
			if ((i & (1 << j)) != 0)
				printf("%d", subset[j]);
		}
		printf("\n");
	}

}

int main() {

	int v[] = {1, 2, 3};

	int s[100] = {0};
	int u[100] = {0};

	printf("*** Laboratorul 6 - Backtracking ***\n");

	printf("\n** Exercitiul 1 **\n");

	printf("\nPermutarile generate sunt:\n\n");
	genPermutations(3, 1, s, u);

	printf("\n** Exercitiul 2 **\n");

	printf("\nSubmultimile generate sunt:\n");
	genSubsets(v, 3);

	printf("\n** Exercitiul 3 **\n");

	printf("\nProblema damelor\n\n");
	genQueens(4, 1, s);


	return 0;
}