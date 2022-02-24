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

void mirror(char *s)
{
	/* TODO */
	int l, i; 
    char *begin_ptr, *end_ptr, ch; 
  
    // Get the length of the string 
    l = strlen(str); 
  
    // Set the begin_ptr and end_ptr 
    // initially to start of string 
    begin_ptr = str; 
    end_ptr = str; 
  
    // Move the end_ptr to the last character 
    for (i = 0; i < l - 1; i++) 
        end_ptr++; 
  
    // Swap the char from start and end 
    // index using begin_ptr and end_ptr 
    for (i = 0; i < l / 2; i++) { 
  
        // swap character 
        ch = *end_ptr; 
        *end_ptr = *begin_ptr; 
        *begin_ptr = ch; 
  
        // update pointers positions 
        begin_ptr++; 
        end_ptr--; 
    } 
	
	
}

int main()
{
	/* TODO: Test function */

	// Get the string 
    char str[100] = "GeeksForGeeks"; 
    printf("Enter a string: %s\n", str); 
  
    // Reverse the string 
    reverseString(str); 
  
    // Print the result 
    printf("Reverse of the string: %s\n", str); 
  
    return 0; 
}

