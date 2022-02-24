#include <stdio.h>

/**
 * Afisati adresele elementelor din vectorul "v" impreuna cu valorile
 * de la acestea.
 * Parcurgeti adresele, pe rand, din octet in octet,
 * din 2 in 2 octeti si apoi din 4 in 4.
 */

int main() {
	int v[] = {0xCAFEBABE, 0xDEADBEEF, 0x0B00B135, 0xBAADF00D, 0xDEADC0DE};

	int i;

	printf("Din octet in octet\n\n");
	for(i = 0; i<5; i++)
	{
		unsigned char *first_byte = *((unsigned char*) &v[i]);
		unsigned char *second_byte = *((unsigned char*) &v[i] + 1);
		unsigned char *third_byte = *((unsigned char*) &v[i] + 2);
		unsigned char *fourth_byte = *((unsigned char*) &v[i] + 3);

		printf("%p -> 0x%x\n", first_byte, &first_byte);
		printf("%p -> 0x%x\n", second_byte, &second_byte);
		printf("%p -> 0x%x\n", third_byte, &third_byte);
		printf("%p -> 0x%x\n", fourth_byte, &fourth_byte);
	}

	printf("\n");
	printf("Din doi in doi octeti\n\n");
	for(i = 0; i<5; i++)
	{
		unsigned char *first_byte = *((unsigned char*) &v[i]);
		unsigned char *second_byte = *((unsigned char*) &v[i] + 1);
		unsigned char *third_byte = *((unsigned char*) &v[i] + 2);
		unsigned char *fourth_byte = *((unsigned char*) &v[i] + 3);

		printf("%p -> 0x%x\n", first_byte, &first_byte);
		printf("%p -> 0x%x\n", third_byte, &third_byte);
	}

	printf("\n");
	printf("Din patru in patru octeti\n\n");
	for(i = 0; i<5; i++)
	{
		unsigned char *first_byte = *((unsigned char*) &v[i]);
		unsigned char *second_byte = *((unsigned char*) &v[i] + 1);
		unsigned char *third_byte = *((unsigned char*) &v[i] + 2);
		unsigned char *fourth_byte = *((unsigned char*) &v[i] + 3);

		printf("%p -> 0x%x\n", first_byte, &first_byte);
		printf("%p -> 0x%x\n", fourth_byte, &fourth_byte);
	}



    return 0;
}
