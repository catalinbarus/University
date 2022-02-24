#include <stdio.h>
#include <stdlib.h>

int n = 10;          
int n2 = 12;
int adjMat1[100][100];     
int adjMat2[100][100];      
int distance_bfs[100][100];  
int visit_bfs[100];
int parents_bfs[100];       
int visit_dfs[100];
int d_dfs[100];       
int f_dfs[100];       
int parents_dfs[100];      
int time_dfs;  

struct queue {
  int begin; 
  int size;  
  int elements[]; 
};


struct queue *create_queue() {
  struct queue *q = (struct queue *)malloc(100 * sizeof(struct queue));
  q->size = 0;  
  q->begin = 0; 
  return q;
}

struct queue *enqueue(struct queue *q, int elem) {
  q->elements[q->size] = elem;
  q->size = q->size + 1;  
  return q;
}


struct queue *top(struct queue *q, int *x) {
  *x = q->elements[q->begin]; 
  return q;
}


struct queue *dequeue(struct queue *q) {
  q->begin = q->begin + 1; 
  return q;
}


int is_empty(struct queue *q) {
 
  if (q->size == q->begin) {
    return 1; 
  }
  return 0;
}

// functia care printeaza o coada (folosita pentru parcurgerea in latime)
void print_queue(struct queue *q) {
  
  printf("   \tQ = {");

  for (int i = q->begin; i < q->size; ++i) {

    if (i < q->size - 1) {

      printf("%c, ", (char)q->elements[i] + 65);
    } else {

      printf("%c", (char)q->elements[i] + 65);
    } 
  }

  printf("}\n");

  for (int i = q->begin; i < q->size; ++i) {

    if (visit_bfs[q->elements[i]] == 1) {

      printf("   \t%c: p(%c)=%c, d(%c)=%d, c(%c)=%s\n", (char)q->elements[i] + 65,
           (char)q->elements[i] + 65, (char)parents_bfs[q->elements[i]] + 65,
           (char)q->elements[i] + 65, (*distance_bfs)[q->elements[i]], (char)q->elements[i] + 65, "gri");

    } else {
        printf("   \t%c: p(%c)=%c, d(%c)=%d, c(%c)=%s\n", (char)q->elements[i] + 65,
           (char)q->elements[i] + 65, (char)parents_bfs[q->elements[i]] + 65,
           (char)q->elements[i] + 65, (*distance_bfs)[q->elements[i]], (char)q->elements[i] + 65, "alb");
    }
  }
}

void BFS(int n, int adjMat[100][100]) {
  int i; 
  int t;
  int prev_elem = -1;

  for (i = 0, t = 1; i < n; ++i) {
    if (visit_bfs[i] == 0) {         

      struct queue *q = create_queue(); 
      q = enqueue(q, i);               
      distance_bfs[i][i] = 0;   
      visit_bfs[i] = 1; 

      printf("\nSC: %c\n", (char)i + 65);

      while (is_empty(q) == 0) { 

        printf("Step %d: \n", t++);
        print_queue(q);     

        if (prev_elem != -1) { 

          printf("  \tc(%c)=negru\n\n", (char)prev_elem + 65);
        } else {

          printf("\n");
        }

        int current_elem;          
        q = top(q, &current_elem);
        int j;                    

        for (j = 0; j < n; ++j) {

          if ((adjMat[current_elem][j] == 1) && (visit_bfs[j] == 0)) {

            q = enqueue(q, j);                       
            distance_bfs[i][j] = distance_bfs[i][current_elem] + 1;
            parents_bfs[j] = current_elem; 
            visit_bfs[j] = 1;     
          }
        }

        visit_bfs[current_elem] = 1; 
        q = dequeue(q);                
        prev_elem = current_elem;      
    }
  }

  printf("Step %d:\n   \tQ = { }\n\tc(%c)=negru\n", t, (char)prev_elem + 65);
}
}

void explore(int n, int u, int p, int adjMat[100][100]) {
  d_dfs[u] = ++time_dfs; 
  int j;                 
  visit_dfs[u] = 1;   
  
  printf("\n%d. %c - c(%c)=gri d(%c)=%d p(%c)=%c", d_dfs[u], (char)u + 65, (char)u + 65,
         (char)u + 65, d_dfs[u], (char)u + 65, (char)p + 65);

  for (j = 0; j < n; ++j) {
    
    if (adjMat[u][j] == 1 && visit_dfs[j] == 0) {

      parents_dfs[j] = u; 
      explore(n, j, u, adjMat);
    }
  }

  f_dfs[u] = ++time_dfs; 
  printf("\n%d. %c - c(%c)=negru f(%c)=%d", f_dfs[u], (char)u + 65, (char)u + 65,
         (char)u + 65, f_dfs[u]);

  visit_dfs[u] = 2;
}

void DFS(int n, int adjMat[100][100]) {
  
    if (visit_dfs[0] == 0) {
      printf("\n\t\t---\nNod start: %c", (char)0 + 65);
      explore(n, 0, -20, adjMat);
      int j;
      time_dfs = 0;
      for (j = 0; j < n; j++) {
        if (j != 0) {
         
          d_dfs[j] = 0;
          f_dfs[j] = 0;
          visit_dfs[j] = 0;
        }
      }
    }
  
}

// functia main
int main() {
  // muchiile grafului
  adjMat1[0][1] = 1; // (A,B)
  adjMat1[0][2] = 1; // (A,C)
  adjMat1[0][7] = 1; // (A,H)
  adjMat1[1][3] = 1; // (B,D)
  adjMat1[1][4] = 1; // (B,E)
  adjMat1[1][7] = 1; // (B,H)
  adjMat1[1][8] = 1; // (B,I)
  adjMat1[2][3] = 1; // (C,D)
  adjMat1[3][4] = 1; // (D,E)
  adjMat1[3][9] = 1; // (D,J)
  adjMat1[4][5] = 1; // (E,F)
  adjMat1[4][6] = 1; // (E,G)
  adjMat1[5][6] = 1; // (F,G)
  adjMat1[7][8] = 1; // (H,I)
  adjMat1[8][0] = 1; // (I,A)

  adjMat2[0][1] = 1; // (A, B)
  adjMat2[0][6] = 1; // (A, G)
  adjMat2[1][2] = 1; // (B, C)
  adjMat2[1][6] = 1; // (B, G)
  adjMat2[2][3] = 1; // (C, D)
  adjMat2[2][4] = 1; // (C, E)
  adjMat2[4][5] = 1; // (E, F)
  adjMat2[6][7] = 1; // (G, H)
  adjMat2[7][0] = 1; // (H, A)
  adjMat2[8][9] = 1; // (I, J)
  adjMat2[8][10] = 1; // (I, K)
  adjMat2[9][10] = 1; // (J, K)
  adjMat2[10][11] = 1; // (K, L)


  printf("\n------------------------------\n");
  printf("\n--- Parcurgere pe latime --- \n");
  BFS(n, adjMat1); // parcurgerea in latime
  printf("\n------------------------------\n--- Parcurgere pe adancime ---\n");
  DFS(n, adjMat1); // parcurgerea in adancime

  for (int i = 0; i < 100; i++) {

    visit_bfs[i] = 0; 
    parents_bfs[i] = 0;      
    visit_dfs[i] = 0; 
    d_dfs[i] = 0;      
    f_dfs[i] = 0;      
    parents_dfs[i] = 0;
  }
  time_dfs = 0;

  for (int i = 0; i < 100; i++) {

    for (int j = 0; j < 100; j++) {
      distance_bfs[i][j] = 0;
    }
  }

  printf("\n------------------------------\n");
  printf("\n--- Parcurgere pe latime --- \n");
  BFS(n2, adjMat2); // parcurgerea in latime
  printf("\n------------------------------\n--- Parcurgere pe adancime ---\n");
  DFS(n2, adjMat2); // parcurgerea in adancime


  printf("\n------------------------------\n");
  return 0;
}