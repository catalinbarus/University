#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <string.h>

void schimba(char *x, char *y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

int alreadyHere(char *current_str, char **printed_str, int len)
{
  int i;
  for (i = 0; i < len; i++) 
  {
    if (strcmp(current_str, printed_str[i]) == 0)
    {
      return 1;
    }
  }
  return 0;
}

void permutare(char *a, int l, int n, char **already_printed, int len)
{
  if (l >= n)
  {
    printf("\t%s\n", a); 
    return;
  }
 
  int i;
  
  for (i = 0; i < n; i++)
  {
    
    if (alreadyHere(a, already_printed, len))
    {
      continue;
    }
    
    schimba((a + l), (a + i));
    
    permutare(a, l + 1, n, already_printed, len);
    
    strcpy(already_printed[len++], a);
    
    schimba((a + l), (a + i));
  }
}

void printare_solutie_garduri(int k, int L)
{
  
  int j;
 
  char *a = (char *)malloc(L * sizeof(char));
  for (j = 0; j < L; j++)
  {
    strcpy((a + j), "|");
  }

  char **str = (char **)malloc(50 * sizeof(char *));
  for (j = 0; j < 50; j++)
  {
    str[j] = (char *)malloc(L * sizeof(char));
  }

  permutare(a, 0, L - 1, str, 0);

  for (j = 0; j < 10; j++)
  {
    free(str[j]);
  }

  free(str);

  int init_len = L;
  int nr_egaluri = 0;
  
  while ((L - k) >= 0)
  {
    char **str_egal = (char **)malloc(50 * sizeof(char *));
    for (j = 0; j < 50; j++)
    {
      str_egal[j] = (char *)malloc(10 * sizeof(char));
    }

    nr_egaluri++;
    L -= k;

    char *single_str_egal = (char *)malloc(50 * sizeof(char));
    
    int index = 0;
    
    for (j = 0; j < nr_egaluri; j++)
    {
      strcpy((single_str_egal + j), "=");
      index++;
    }
    
    for (j = 0; j < L; j++, index++)
    {
      strcpy((single_str_egal + index), "|");
    }

    permutare(single_str_egal, 0, init_len - nr_egaluri, str_egal, 0);

    for (j = 0; j < 50; j++)
    {
      free(str_egal[j]);
    }
    free(str_egal);
  }
}

void fence(int n, int k)
{
  int v[n];
  int i = 3;

  v[1] = 1;
  v[2] = 2;

  for (; i <= n; i++)
  {
    v[i] = v[i - 1] + v[i - k];
  }

  printf("solutii obtinute:\n");
  for (i = 1; i <= n; i++)
  {
    printf("\nv[%d] = %d\n", i, v[i]);
    printare_solutie_garduri(k, i);
  }
  printf("-----\n");

  printf("Numarul de combinatii posibile este: %d\n", v[n]);
}


void print_sume(int v[], int index, int sum, int rest, int sol[], int index_sol,
                int n)
{
  if (index == -1)
  {
    return;
  }
  
  print_sume(v, index - 1, sum, rest, sol, index_sol, n);
 
  if (((sum + v[index]) % 3) == rest)
  {
    sol[index_sol++] = v[index];
    
    printf("%d = ", sum + v[index]);
    int j;
   
    for (j = 0; j < index_sol; j++)
    {
      if (index_sol >= 2 && j < index_sol - 1) {
        printf("%d + ", sol[j]);
      } 
      else {
        printf("%d ", sol[j]);
      }
    }
    printf("\n\t\t");
  }
 
  if (((sum + v[index]) % 3) != rest)
  {
    
    sol[index_sol++] = v[index];
    print_sume(v, index - 1, sum + v[index], rest, sol, index_sol, n);
  }
  else
  {
    print_sume(v, index - 1, sum + v[index], rest, sol, index_sol, n);
  }
}

void sume(int v[], int n)
{

  int D[n + 1][3];
  
  D[0][0] = 0;
  D[0][1] = 0;
  D[0][2] = 0;

  int i;
  for (i = 1; i <= n; i++)
  {
    if (v[i - 1] % 3 == 0) 
    {
      D[i][0] = 1 + 2 * D[i - 1][0]; 
      D[i][1] = 2 * D[i - 1][1];    
      D[i][2] = 2 * D[i - 1][2];    
    }
    else if (v[i - 1] % 3 == 1) 
    {
      D[i][0] = D[i - 1][0] + D[i - 1][1]; 
      D[i][1] =
          1 + D[i - 1][0] + D[i - 1][1];   
      D[i][2] = D[i - 1][2] + D[i - 1][1]; 
    }
    else
    {
      D[i][0] = D[i - 1][0] + D[i - 1][1]; 
      D[i][1] = D[i - 1][2] + D[i - 1][1]; 
      D[i][2] =
          1 + D[i - 1][2] + D[i - 1][0]; 
    }
    
    if (i == n) {
      int empty_sol[n]; 
      int len = 0;      
      
      printf("\n\t\t");
      print_sume(v, i - 1, 0, 0, empty_sol, len, n);
      len = 0;
    }
    
   
  }
  
  printf("\nNumarul de sume care dau restul 0 la impartirea cu 3 este egal cu "
         "%d.\n",
         D[n][0]);
  printf("-----\n");
}


int main() {


  int arr[]={3, 1, 2, 4};
  int l=4;
  int k =2, n = 6;

  printf("*** Lab 5 PA - Programare Dinamica ***\n\n");

  printf("** Exercitiul 2: Problema gardurilor **\n\n");

  fence(n, k);

  printf("\n** Exercitiul 3: Problema sume **\n\n");
  
  printf("Sumele posibile sunt:\n");
  sume(arr, l);
  
  return 0;
 }