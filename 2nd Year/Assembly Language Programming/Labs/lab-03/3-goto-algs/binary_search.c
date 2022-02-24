#include <stdio.h>

void main(void)
{
	int v[] =  {1, 2, 15, 51, 53, 66, 202, 7000};
	int dest = v[2]; /* 15 */
	int start = 0;
	int end = sizeof(v) / sizeof(int) - 1;

	/* TODO: Implement binary search */

	int middle = (start + end) / 2;

	again:
	if(start <= end)
	{
		goto step1;
	}

	step1:
	if(v[middle] < dest)
	{
		goto increment;
		//start = middle + 1;
		//goto step2;
	}

	goto next;

	increment:
		start = middle + 1;
		goto step2;

	next:
	if(v[middle] == dest)
	{
		printf("Found at index %d. (Indexing starts from 0.)\n", middle);
		goto end;
	}

	if(v[middle] > dest)
	{
		//end = middle - 1;
		//goto step2;
		goto decrement;
	}

	decrement:
		end = middle - 1;
		goto step2;

	step2:
	middle = (start + end) / 2;

	if(start <= end)
	{
		goto again;
	}

	if(start > end)
	{
		printf("Not found.\n");
		goto end;
	}

	end:
		return 0;
}
