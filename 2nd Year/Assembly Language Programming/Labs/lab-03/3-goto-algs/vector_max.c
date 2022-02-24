#include <stdio.h>

void main(void)
{
	int v[] = {4, 1, 2, -17, 15, 22, 6, 2};
	int max = 0;
	int i = 0;
	int n = sizeof(v) / sizeof(*v);

	/* TODO: Implement finding the maximum value in the vector */

	next:
	if(i < n && v[i] > max)
		goto increment;

	if(i<n)
		goto increment2;

	increment:
		max = v[i];
		i++;

	goto next2;


	increment2:
		i++;

	next2:
	if(i < n)
		goto next;

	if(i == n)
		goto end;

	end:
	printf("%d\n", max);	
}
