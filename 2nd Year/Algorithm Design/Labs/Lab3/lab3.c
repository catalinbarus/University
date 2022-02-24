#include<stdio.h>
 
void knapsack(int n, float greutate[], float profit[], float capacitate) {
   float x[20], tp = 0;
   int i, M;
   char percentage[] = "%";
   M = capacitate;
 
   for (i = 0; i < n; i++)
      x[i] = 0.0;
 
   for (i = 0; i < n; i++) {
      if (greutate[i] > M)
         break;
      else {
         x[i] = 1.0;
         tp = tp + profit[i];
         M = M - greutate[i];
      }
   }
 
   if (i < n)
      x[i] = M / greutate[i];
 
   tp = tp + (x[i] * profit[i]);
 
   printf("\nProcentajele luate din fiecare obiect: \n");
   
   for (i = 0; i < n; i++)
      printf("%f%s din masa totala de: %f KG.\n", x[i] * 100, percentage, greutate[i]);
 
   printf("\nProfitul maxim este: %f\n", tp);
 
}


void spectacol(int n, int ora_inceput[], int ora_sfarsit[])
{

	int nr_spectacole[150], i, aux, ok, j;

	for(i = 0; i < n; i++)
	{
		nr_spectacole[i] = i + 1;
	}

    do
    {

    	ok = 0;

    	for(i = 0; i <= n; i ++)
    	{
    		if(ora_sfarsit[nr_spectacole[i]] > ora_sfarsit[nr_spectacole[i + 1]])
    		{
				aux = nr_spectacole[i];
				nr_spectacole[i] = nr_spectacole[i + 1];
				nr_spectacole[i + 1] = aux;
				ok = 1;
    		}
    	}

    }while(ok);

    printf("Spectacolele alese : \n");

    j = 0;
    int cnt = 0;

    for(i = 2; i <= n + 1; i++)
    {
    	if(ora_inceput[nr_spectacole[i]] >= ora_sfarsit[nr_spectacole[j]])
    	{
    		printf("(%d, %d) ", ora_inceput[nr_spectacole[i]], ora_sfarsit[nr_spectacole[i]]);
    		j = i;
    		cnt++;
    	}
    }

    printf("\n");
    printf("Numarul total de spectacole : %d\n", cnt);

}

int main() {


   float greutate[20], profit[20], capacitate;
   int num, i, j;
   float ratio[20], temp;

   printf("*** Laborator 3 - PA ***\n\n");

   printf("** Problema 2 - Problema rucsacului **\n");
 
   printf("\nCate obiecte avem disponibile? ");
   scanf("%d", &num);
 
   printf("\nCate kg si ce valoare are fiecare obiect? \n");
   for (i = 0; i < num; i++) {
      scanf("%f %f", &greutate[i], &profit[i]);
   }
 
   printf("\nCe capacitate are rucsacul? ");
   scanf("%f", &capacitate);
 
   for (i = 0; i < num; i++) {
      ratio[i] = profit[i] / greutate[i];
   }
 
   for (i = 0; i < num; i++) {
      for (j = i + 1; j < num; j++) {
         if (ratio[i] < ratio[j]) {
            temp = ratio[j];
            ratio[j] = ratio[i];
            ratio[i] = temp;
 
            temp = greutate[j];
            greutate[j] = greutate[i];
            greutate[i] = temp;
 
            temp = profit[j];
            profit[j] = profit[i];
            profit[i] = temp;
         }
      }
   }

   knapsack(num, greutate, profit, capacitate);

   printf("\n** Problema 3 - Problema spectacolelor **\n");

   /*int begin[] = {10, 11, 12, 14, 16, 17};
   int end[] = {11, 13, 13, 18, 17, 19};

   printMaxActivities(begin, end, 6);*/

   int ora_inceput[] = {10, 11, 12, 14, 16, 17};
   int ora_sfarsit[] = {11, 13, 13, 18, 17, 19};

   spectacol(6, ora_inceput, ora_sfarsit);

   printf("\n");


   return 0;
}