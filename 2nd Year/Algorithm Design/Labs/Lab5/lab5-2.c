#include<stdio.h>

int gard(int n, int k)
{
	int v[n];

	for(int i = 0; i<=n; i++)
	{
		v[i] = 0;
	}

	if (n == 0)
		return 0;
	if(n == 1)
		return k;
	v[0] = 1;
	v[1] = 1;

	for(int i = 2; i<=n; i++)
	{
		v[i] = v[i-1] + v[i-k];
	}

	return v[n];
}

int main()
{
	int k =2, n = 6;

	int sol = gard(n, k);

	printf("Nr sol : %d\n", sol);
	
	return 0;
}