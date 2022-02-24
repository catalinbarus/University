#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_strlen(const char *str)
{
	/* TODO */
	int length = 0;
	int i;
	
	for( i = 0; str[i] !=0; i++)
		length++;

	return length;
}

void equality_check(const char *str)
{
	/* TODO */
	int size, i;
	size = my_strlen(str);
	for(i=0; i<size;i++)
		printf("%p\n", &str[i]);
}

int main(void)
{
	/* TODO: Test functions */
	const char *sir = "aac";
	printf("%d\n", my_strlen(sir));
	equality_check(sir);

	return 0;
}

