#include <stdio.h>
#include <limits.h> 


int parantezare(int v[], int dim) {

   int minMatrix[dim][dim];
   int j, q;

   for (int i = 1; i < dim; i++) {
      minMatrix[i][i] = 0;
   }

   for (int L = 2; L < dim; L++) {

      for (int i = 1; i < dim - L + 1; i++) {

         j = i + L - 1;
         minMatrix[i][j] = 99999999;

         for (int k = i; k <= j - 1; k++) {

            q = minMatrix[i][k] + minMatrix[k + 1][j] + v[i - 1] * v[k] * v[j];

            if (q < minMatrix[i][j]){
               minMatrix[i][j] = q;
            }
         }
      }
   }

   printf("*** Laborator 4 - PA ***\n\n");

   printf("** Problema 1 - Parantezarea inmultirii matricelor **\n\n");

   printf("Triunghiul numarului de inmultiri necesare:\n\n");

   for (int i = 1; i < dim; i++) {

   	for (j = 1; j < dim; j++) {
   		printf("%d ", minMatrix[i][j]);
   	}
   	printf("\n");
   }

   return minMatrix[1][dim - 1];
}


int max(int a, int b) { 

   if (a > b) {
      return a;
   }

   return b;
}
 
int rucsacDinamic(int capacity, int weight[], int value[], int numOfItems)
{
   int i, w;
   int K[numOfItems + 1][capacity + 1];
 
   for (i = 0; i <= numOfItems; i++)
   {
       for (w = 0; w <= capacity; w++)
       {
           if (i == 0 || w == 0) {
               K[i][w] = 0;
           }
           else if (weight[i-1] <= w) {
                 K[i][w] = max(value[i - 1] + K[i - 1][w - weight[i - 1]],  K[i - 1][w]);
           }
           else {
                 K[i][w] = K[i - 1][w];
           }
       }
   }
 
   return K[numOfItems][capacity];
}


int maxSubsir(int v[], int begin, int end, int lastMin)
{
    if (begin == end) {
        return 0;
    }

    int excl = maxSubsir(v, begin + 1, end, lastMin);
    int incl = 0;

    if (v[begin] > lastMin) {
        incl = 1 + maxSubsir(v, begin + 1, end, v[begin]);
    }
 
    return max(incl, excl);
}

int main() {

   int v[] = {2, 4, 3, 5, 2};
   int dim = 5;
   printf("\nNumarul minim de inmultiri este de: %d\n\n", parantezare(v, dim));

   printf("** Problema 2 - Problema discreta a rucsacului **\n\n");

   int numOfItems = 3;
   int capacity = 50;

   int weight[] = {10, 30, 20};
   int value[] = {60, 120, 100};

   printf("Valoarea totala este: %d\n\n", rucsacDinamic(capacity, weight, value, numOfItems));

   printf("** Problema 3 - Cel mai lung subsir crescator **\n\n");

   int v1[] = {1, 2, 9, 3, 8, 4, 7};

   printf("%d\n", maxSubsir(v1, 0, 7, INT_MIN));

   return 0;
}