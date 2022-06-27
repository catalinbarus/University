/**
 * SO
 * Lab #5, Memory Management
 *
 * Task #7, Linux
 *
 * Use of mcheck
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/utils.h"

char first_name[] = "  Harry";
char last_name[]  = "    Potter";

static char *trim(char *s)
{
	char *aux;
	char *p = malloc(strlen(s) + 1);

	aux = p;
	strcpy(p, s);

	while (*p == ' ')
		p++;

	strcpy(s, p);
	free(aux);

	return s;
}

int main(void)
{

	printf("%s %s is learning SO!\n",
			trim(first_name), trim(last_name));

	return 0;
}
