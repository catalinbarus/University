#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* delete_first(char *s, char *pattern)
{
	char s_1[100], p_1[100];

	strcpy(s_1, s);
	strcpy(p_1, pattern);

	char *copy;
	copy = strstr(s_1, p_1);

	char copy2[100], copy3[100];
	strcpy(copy2, copy);
	strcpy(copy3, copy);

	memmove(copy2, copy2+strlen(p_1), strlen(copy2)-strlen(p_1)+1);
	memmove(s_1+((strlen(s_1)-strlen(copy3))), copy2, strlen(copy2));
	s_1[strlen(s_1)-strlen(p_1)] = '\0';

	char *final;

	final = strdup(s_1);

	return final;
}




int main(){
	
	char *s = "Ana are mere";
	char *pattern = "re";

	// Decomentati linia dupa ce ati implementat functia delete_first.
	printf("%s\n", delete_first(s, pattern));

	return 0;
}
