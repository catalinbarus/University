#include <stdio.h>
#include <stdlib.h>

int minimum(int a, int b) {

  if (a < b) {

    return a;
  }

  return b;
}

// graful folosit
int n = 10;    // numarul de noduri din graf
int Graph[10][10]; // graful

// variabilele folosite pentru punctele de articulatie
int low_art[10];     // low
int d_art[10];       // d
int art[10];         // art
int vizitat_art[10]; // c
int timp_art;        // variabila timp
int subarb_art[10];  // subarb
int p_art[10];       // p

// variabilele folosite pentru punti
int timp_punti;        // variabila timp
int vizitat_punti[10]; // c
int d_punti[10];       // d
int p_punti[10];       // p
int low_punti[10];     // low
int punte[10][2];      // punte
int nr_punti;          // nr de punti

void exploreaza_art(int u) {

  d_art[u] = low_art[u] = timp_art++; 
  vizitat_art[u] = 1;                 

  for (int v = 0; v < n; v++) {            

    if (Graph[u][v] == 1 || Graph[v][u] == 1) { 

      if (vizitat_art[v] == 0) {        

        p_art[v] = u;                   
        subarb_art[u]++;   
        exploreaza_art(v);
        low_art[u] = minimum(low_art[u], low_art[v]);

        if (p_art[u] != -1 && low_art[v] >= d_art[u]) {

          art[u] = 1; 
        }
      } else if (p_art[u] != v) { 

        low_art[u] = minimum(low_art[u], d_art[v]);
      }
    }
  }
}

void alg_tarjan() { 

  for (int i = 0; i < n; ++i) {

    p_art[i] = -1; 
  }

  for (int i = 0; i < n; ++i) {   

    if (vizitat_art[i] == 0) { 

      exploreaza_art(i);      
      if (subarb_art[i] > 1) { 

        art[i] = 1;           
      }
    }
  }

  
  int nr_art = 0;
  printf("Punctele de articulatie sunt:\n");

  for (int i = 0; i < n; ++i) {

    if (art[i] == 1) {

      nr_art++;
      printf("\t%d\n", i);
    }
  }

  printf("Numarul de puncte de articulatie este: %d\n\n", nr_art);
}

void exploreaza_punti(int u) {

  d_punti[u] = low_punti[u] = timp_punti++; 
  vizitat_punti[u] = 1;                    
 
  for (int v = 0; v < n; ++v) {             

    if (Graph[u][v] == 1 || Graph[v][u] == 1) { 

      if (vizitat_punti[v] == 0) {     

        p_punti[v] = u;                
        exploreaza_punti(v);           
        low_punti[u] = minimum(low_punti[u], low_punti[v]); 
        if (low_punti[v] > d_punti[u]) {                

          punte[nr_punti][0] = v;
          punte[nr_punti][1] = u;
          nr_punti++;
        }
      } else if (p_punti[u] != v) {

        low_punti[u] = minimum(low_punti[u], d_punti[v]);
      }
    }
  }
}

void punti_tarjan() { 

  for (int i = 0; i < n; ++i) {

    p_punti[i] = -1;
  }
  for (int i = 0; i < n; ++i) {     

    if (vizitat_punti[i] == 0) {

      exploreaza_punti(i);     
    }
  }

  printf("Puntile din graf sunt:\n");
  for (int i = 0; i < nr_punti; ++i) {

    printf("\t%d - %d\n", punte[i][0], punte[i][1]);
  }

  printf("Numarul de punti din graf este: %d\n\n", nr_punti);
}

int main() {
  
  Graph[0][1] = 1;
  Graph[0][9] = 1;
  Graph[1][2] = 1;
  Graph[1][8] = 1;
  Graph[2][3] = 1;
  Graph[2][4] = 1;
  Graph[2][7] = 1;
  Graph[3][4] = 1;
  Graph[3][5] = 1;
  Graph[5][6] = 1;
  Graph[7][8] = 1;

  printf("*** Laborator 9 PA ***\n\n");

  printf("\n*** Exercitiul 1: Puncte de articulatie ***\n\n");
  alg_tarjan();

  printf("\n*** Exercitiul 2: Punti ***\n\n");
  punti_tarjan();

  return 0;
}