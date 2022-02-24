#include <stdio.h>
#include <stdlib.h>

int G[10][10]; 
int n = 7;    

int dist_djk[7]; 
int p_djk[7];    

int dist_bf[7]; 
int p_bf[7];   


int *extrage_min(int *q, int *size, int *elem) {
  int i;
  int min = 1000000;            
  int index = -1;                
  for (i = 1; i <= *size; ++i) {
    if (dist_djk[q[i]] < min) {  
      min = dist_djk[q[i]];      
      index = i;                
    }
  }
  *elem = q[index];    
  q[index] = q[*size]; 
  (*size)--;          
  return q;
}


void dijkstra() {

  int *q = (int *)malloc(n * sizeof(int)); 
  int q_size = 0;                          
  int i;

  for (i = 1; i <= n; ++i) {

    p_djk[i] = -1;
    dist_djk[i] = 1000000;
  }

  dist_djk[1] = 0;           
  for (i = 1; i <= n; ++i) {

    q[i] = i;
    ++q_size;
  }

  int elem_curent;
  int acc = 1;

  printf("** Algoritmul Dijkstra **\n\n");

  printf("Coada la pasul %d: ", acc);
  printf("Q = {");

  for (i = 1; i <= q_size; i++) {

    if (i != q_size) {
      printf("%d ", q[i]);
    } else {
      printf("%d", q[i]);
    }
  }
    printf("}");
  acc++;
  printf("\n\n");

  for (i = 1; i <= n; i++) {

      printf("p[%d] = %d, d[%d] = %d\n", i, p_djk[i], i, dist_djk[i]);
  }
  printf("\n");

  while (q_size > 0) { 

    q = extrage_min(q, &q_size, &elem_curent);
    printf("Coada la pasul %d: ", acc);
    acc++;

    printf("Q = {");
    for (i = 1; i <= q_size; i++) {

      if (i != q_size) {
        printf("%d ", q[i]);
      } else {
        printf("%d", q[i]);
      }
    }
    printf("}");

    printf("\n\n");

    for (i = 1; i <= n; i++) {               

      if (G[elem_curent][i] != 0) {           

        if (dist_djk[i] > dist_djk[elem_curent] + G[elem_curent][i]) {

          dist_djk[i] = dist_djk[elem_curent] + G[elem_curent][i];
          p_djk[i] = elem_curent;
        }
      }
    }

    for (i = 1; i <= n; i++) {

      printf("p[%d] = %d, d[%d] = %d\n", i, p_djk[i], i, dist_djk[i]);
    }
    printf("\n");

  }
 
  printf("\n** Rezultate finale Dijkstra **\n\n");

  for (i = 1; i <= n; ++i) {

    printf("\tnod %d, d=%d, p=%d\n", i, dist_djk[i], p_djk[i]);
  }

  printf("\n-----------------------\n");
  free(q);
}


void bellman_ford() {
  int i;
  for (i = 1; i <= n; ++i) {

    dist_bf[i] = 100000000; 
    p_bf[i] = -1;           
  }

  printf("\n** Algoritmul Bellman-Ford **\n\n");

  dist_bf[1] = 0;                  
  for (i = 1; i <= (n - 1); ++i) { 

    printf("Pasul %d:\n", i);
    int j;

    for (j = 1; j <= n; ++j) { 

      int k;
      for (k = 1; k <= n; ++k) {

        printf("%d -> %d : ", j, k);

        if (G[j][k] != 0) { 

          int cost_drum = G[j][k];

          if (dist_bf[k] > dist_bf[j] + cost_drum) {

            
            dist_bf[k] = dist_bf[j] + cost_drum;
            p_bf[k] = j;
          }
        }
        
        printf("d[%d] = %d, p[%d] = %d\n", k, dist_bf[k], k, p_bf[k]);
      }
    }

    printf("\n");
  }

  
  printf("\n** Rezultate finale Bellman-Ford **\n\n");

  for (i = 1; i <= n; ++i) {

    printf("\tnod %d, d=%d, p=%d\n", i, dist_bf[i], p_bf[i]);
  }

  printf("\n-----------------------\n");
}

int main() {
  
  G[1][2] = 3;
  G[1][3] = 4;
  G[1][5] = 1;
  G[1][6] = 10;
  G[1][7] = 3;
  G[2][3] = 2;
  G[3][4] = 2;
  G[3][6] = 2;
  G[5][4] = 3;
  G[5][7] = 1;
  G[6][4] = 2;
  G[7][3] = 1;
  G[7][4] = 10;
  G[7][5] = 2;

  printf("*** Laboratorul 10 PA ***\n\n");
  dijkstra();
  bellman_ford();
  return 0;
}