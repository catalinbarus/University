#include <stdlib.h>
#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

int G[12][12]; 
int n = 12; 

int dist_prim[12]; 
int p_prim[12]; 
int inclus_prim[12]; 

int *constrQ(int *q, int *size, int sursa) {
	int i;
	for(i = 0; i < n; ++i) {
		q[*size] = i;
		(*size)++;
	}
	return q;
}

int *extrageMin(int *q, int *e, int *size) {
	
	int min = 1000000000;
	int index = -1;
	int i;
	for(i = 0; i < *size; ++i) {
		if(dist_prim[q[i]] < min) { 
			index = i;
			min = dist_prim[q[i]];
		}
	}
	
	*e = q[index];
	
	q[index] = q[*size - 1];
	(*size)--;
	return q;
}

void prim() {
	
	printf("\n** ALGORITMUL LUI PRIM **\n\n");
	int *q = (int *) malloc(n * sizeof(int));
	int q_size = 0; 
	int ama_size = 0; 
	int AMA[50][2];
	int i;
	int elem; 
	for(i = 0; i < n; ++i) {
		dist_prim[i] = 1000000000;
		p_prim[i] = -1;
	}
	dist_prim[8] = 0;
	q = constrQ(q, &q_size, 8);
	int pas = 1; 
	while(q_size > 0) {
	
		q = extrageMin(q, &elem, &q_size);
		printf("pasul %d - se extrage nodul (%c) p=%c\n", pas++,
			(char) elem + 65, (char) p_prim[elem] + 65);
		AMA[ama_size][0] = elem;
		AMA[ama_size][1] = p_prim[elem];
		ama_size++;
		int j;
		for(j = 0; j < n; ++j) { 
			if(G[elem][j] != 0 || G[j][elem] != 0) { 
				int d = G[elem][j] + G[j][elem];
				if(d < dist_prim[j]) {
					
					p_prim[j] = elem;
					dist_prim[j] = d;
				}
			}
		}

		for (i = 0; i < n; i++) {
			printf("p[%c] = %d, d[%c] = %d\n", i + 65, p_prim[i], i + 65, dist_prim[i]); 
		}
		printf("\n");
	}
	
	printf("\n\n** REZULTATE ALGORITMUL LUI PRIM **\n");
	printf("\n* muchiile din AMA sunt *\n");
	for(i = 1; i < ama_size; ++i) {
		printf("\t%c - %c\n", (char)AMA[i][0] + 65, (char)AMA[i][1] + 65);
	}
	
	free(q);
}


int *alegeArb(int index1, int index2, int *v) {
	int v1 = v[index1];
	int v2 = v[index2];
	int m = min(v1, v2);
	int i;
	for(i = 0; i < n; ++i) {
		if(v[i] == v1 || v[i] == v2) {
			v[i] = m;
		}
	}
	return v;
}


void kruskal() {
	printf("** ALGORITMUL LUI KRUSKAL **\n\n");
	int *arb_kruskal = (int *) malloc(n * sizeof(int)); 
	int muchii_kruskal[50][3];
	int muchii_AMA[50][2];
	int nr_muchii = 0; 
	int i; 
	int ama_size = 0;

	for(i = 0; i < n; ++i) {
		arb_kruskal[i] = i;
		int j;
		for(j = 0; j < n; ++j) {
			if(G[i][j] != 0) {
				muchii_kruskal[nr_muchii][0] = i;
				muchii_kruskal[nr_muchii][1] = j;
				muchii_kruskal[nr_muchii][2] = G[i][j];
				nr_muchii++;
			}
		}
	}

	for(i = 0; i < nr_muchii; ++i) {
		
		int min = 1000000000;
		int index_min = -1;
		int j;
		
		for(j = 0; j < nr_muchii; ++j) {
			if(muchii_kruskal[j][2] < min) {
				min = muchii_kruskal[j][2];
				index_min = j;
			}
		}
		int u = muchii_kruskal[index_min][0];
		int v = muchii_kruskal[index_min][1];
		printf("pas %d - muchia %c-%c de cost=%d\n", i, (char)u + 65,
			(char)v + 65, muchii_kruskal[index_min][2]);
		
		muchii_kruskal[index_min][2] = 1000000000;
		if(arb_kruskal[u] != arb_kruskal[v]) {
			
			printf("\t se adauga in AMA\n");
			arb_kruskal = alegeArb(u, v, arb_kruskal); 
			
			muchii_AMA[ama_size][0] = u; 
			muchii_AMA[ama_size][1] = v;
			ama_size++;
		} else {
			printf("\t NU se adauga in AMA\n");
		}
	}
	
	printf("\n\n** REZULTATE ALGORITMUL LUI KRUSKAL **\n"
			"* muchiile din graf sunt *\n");
	for(i = 0; i < ama_size; ++i) {
		printf("\t%c - %c\n", (char)muchii_AMA[i][0] + 65,
					(char)muchii_AMA[i][1] + 65);
	}
	
	free(arb_kruskal);
}

int main() {
	
	G[0][8] = 3;
	G[0][1] = 9;
	G[0][6] = 10;
	G[0][7] = 6;
	G[1][6] = 11;
	G[1][2] = 5;
	G[2][3] = 8;
	G[2][4] = 12;
	G[3][5] = 9;
	G[4][5] = 2;
	G[6][7] = 4;
	G[8][9] = 5;
	G[9][10] = 14;
	G[10][11] = 7;
	G[8][11] = 8;
	
	printf("** Laboratorul 11 PA **\n\n");
	prim();
	kruskal();
	return 0;
}