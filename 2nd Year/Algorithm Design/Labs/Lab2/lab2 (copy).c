#include <stdio.h>


void Hanoi(int n, char source, char destination, 
			char intermediary) {


	if (n == 1) {

		printf("Mutam discul 1 din sursa %c la destinatia %c\n", source, destination);

		return;
	}

	Hanoi(n - 1, source, intermediary, destination);

	printf("Mutam discul %d din sursa %c la destinatia %c\n", n, source, destination);

	Hanoi(n - 1, intermediary, destination, source);
}

int maxElemInArray(int v[], int left, int right) {

	if (left == right) {
		return v[left];
	}

	int middle = (left + right) / 2;
	int v_1 = maxElemInArray(v, left, middle);
	int v_2 = maxElemInArray(v, middle + 1, right);

	if(v_1 > v_2) {
		return v_1;
	}
	else {
		return v_2;
	}
}

void combina(int v[], int left, int middle, int right) {

	int left_size = middle - left + 1;
	int right_size = right - middle;

	int left_subarray[left_size];
	int right_subarray[right_size];

	for (int i = 0; i < left_size; i++) {
		left_subarray[i] = v[left + i];
	}
	for (int j = 0; j < right_size; j++) {
		right_subarray[j] = v[middle + 1 + j];
	}

	int i = 0, j = 0, k = left;

	while (i < left_size && j < right_size) {
        if (left_subarray[i] <= right_subarray[j]) {
            v[k] = left_subarray[i];
            i++;
        }
        else {
            v[k] = right_subarray[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        v[k] = left_subarray[i];
        i++;
        k++;
    }

    while (j < right_size) {
        v[k] = right_subarray[j];
        j++;
        k++;
    }
}

void interclasare(int v[], int left, int right) {

	if (left >= right) {
		return;
	}

	int middle = (left + right) / 2;
	interclasare(v, left, middle);
	interclasare(v, middle + 1, right);
	combina(v, left, middle, right);
}

int cautareBinara(int v[], int left, int right, int x) {

	if (left > right) {
		return -1;
	}
	else {

		int middle = (left + right) / 2;

		if (v[middle] == x) {
			return x;
		}
		else {

			if (x < v[middle]) {
				cautareBinara(v, left, middle - 1, x);
			}
			else {
				cautareBinara(v, middle + 1, right, x);
			}
		}
	}
}

int numarAparitii(int v[], int left, int right, int x) {

	if ((left > right) || (left == right && v[left] != x)) {
		return 0;
	}

	if (left == right && v[left] == x) {
		return 1;
	}

	int middle = (left + right) / 2;

	return numarAparitii(v, left, middle, x) + 
			numarAparitii(v, middle + 1, right, x);
}


int main() {


	printf("*** Exercitiul 1 - Turnurile din Hanoi ***\n\n");
	int n = 3;
	Hanoi(n, 'A', 'C', 'B');
	printf("\n");

	printf("*** Exercitiul 2 - Maximul elementelor unui vector ***\n\n");

	int v[5] = {3, 2, 5, 2, 4};

	printf("Pentru vectorul:\n[");
	for (int i = 0; i <= 4; i++) {

		if(i != 4) {
			printf("%d, ", v[i]);
		}
		else {
			printf("%d]", v[i]);
		}
	}
	printf("\n\n");
	printf("Maximul este: %d\n\n", maxElemInArray(v, 0, 4));

	printf("*** Exercitiul 3 - Sortare prin interclasare ***\n\n");

	int v1[] = {3, 2, 1, 4, 3, 5, 2};

	printf("Pentru vectorul:\n[");
	for (int i = 0; i <= 6; i++) {

		if(i != 6) {
			printf("%d, ", v1[i]);
		}
		else {
			printf("%d]", v1[i]);
		}
	}
	printf("\n\n");

	interclasare(v1, 0, 6);


	printf("Sortarea prin interclasare este:\n[");
	for (int i = 0; i <= 6; i++) {

		if(i != 6) {
			printf("%d, ", v1[i]);
		}
		else {
			printf("%d]", v1[i]);
		}
	}
	printf("\n\n");

	printf("*** Exercitiul 4 - Cautarea binara ***\n\n");

	int v2[] = {1, 3, 4, 5, 7, 8, 9};
	int search = 3;

	printf("Pentru vectorul:\n[");
	for (int i = 0; i <= 6; i++) {

		if(i != 6) {
			printf("%d, ", v2[i]);
		}
		else {
			printf("%d]", v2[i]);
		}
	}

	printf("\nVrem sa gasim valoarea %d\n\n", search);
	printf("Elementul cu valoarea %d a fost gasit!\n", cautareBinara(v2, 0, 6, search));
	printf("\n\n");

	printf("*** Exercitiul 5 - Aparitiile unui element intr-un vector nesortat ***\n\n");

	int v3[] = {2, 1, 3, 1, 1, 4, 2, 1, 8, 1};
	int x = 1;

	printf("Pentru vectorul:\n[");
	for (int i = 0; i <= 9; i++) {

		if(i != 9) {
			printf("%d, ", v3[i]);
		}
		else {
			printf("%d]", v3[i]);
		}
	}
	printf("\n");

	printf("\nVrem sa vedem de cate ori apare %d in vector\n\n", x);

	printf("Valoarea %d a fost gasita de %d ori!\n", x, numarAparitii(v3, 0, 9, x));

	return 0;
}