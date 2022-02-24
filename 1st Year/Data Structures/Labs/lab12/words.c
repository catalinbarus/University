#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Key;
typedef int Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element** elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f) {
  // Cerinta 1
  
  	*h = (HashTable*)malloc(sizeof(HashTable));
  	if(!*h)
  		return;
  	
  	(*h)->size = size;
  	(*h)->elements = (Element**)malloc(size*sizeof(Element*));
  	if(!(*h)->elements)
  	{
  		free(*h);
  		return;
  	}
  
	for(long i=0; i<size; i++)
		(*h)->elements[i] = NULL;
  	
  	(*h)->hashFunction = f;
}

int exists(HashTable *hashTable, Key key) {
  // Cerinta 1
  
  	Element* elem = hashTable->elements[hashTable->hashFunction(key, hashTable->size)];
	while(elem != NULL)
	{
		if(strcmp(elem->key, key) == 0)
			return 1;
		elem = elem->next;
	}
  
  	return 0;
}

Value get(HashTable *hashTable, Key key) {
  // Cerinta 1
  
	Element* elem = hashTable->elements[hashTable->hashFunction(key, hashTable->size)];
  	while(elem != NULL)
  	{
  		if(strcmp(elem->key, key) == 0)
  			return elem->value;
 	 	elem = elem->next;
	}
  	
  	return (Value)0;
}

void put(HashTable *hashTable, Key key, Value value) {
  // Cerinta 1
  
  	int idx = hashTable->hashFunction(key, hashTable->size);
	
	Element* elem = hashTable->elements[idx];
	if(elem == NULL)
	{
		Element* new_elem = (Element*)malloc(sizeof(Element));
		new_elem->key = (char*)malloc(strlen(key)*sizeof(char));
		strcpy(new_elem->key, key);
		new_elem->value = value;
		hashTable->elements[idx] = new_elem;
		new_elem->next = NULL;
		return;
	}

	while(elem != NULL)
	{
		if(strcmp(elem->key, key) == 0)
		{
			elem->value = value;
			return;
		}
		if(elem->next == NULL)
		{
			Element* new_elem = (Element*)malloc(sizeof(Element));
			new_elem->key = (char*)malloc(strlen(key)*sizeof(char));
			strcpy(new_elem->key, key);
			new_elem->value = value;
			elem->next = new_elem;
			new_elem->next = NULL;
			return;
		}
		elem = elem->next;
	}
  
}

void deleteKey(HashTable *hashTable, Key key) {
  // Cerinta 1
  
	int idx = hashTable->hashFunction(key, hashTable->size);
  
  	Element* elem = hashTable -> elements[idx];
  	Element* prev = NULL;
  	
  	while(elem != NULL)
  	{
  		if(strcmp(elem->key, key) == 0)
  		{
  			if(prev == NULL)
  			{
  				hashTable->elements[idx] = elem->next;
				free(elem->key);
				free(elem);
				return;
  			}
  			else
  			{
  			 	prev->next = elem->next;
  			 	free(elem->key);
  			 	free(elem);
  			 	return; 
  			}
  		}
  		prev = elem;
		elem = elem->next;
  	}
}

void print(HashTable *hashTable) {
  // Cerinta 1
  
  	Element* elem;
	int i, level=1;
	
	int* address=(int*)8;
	for(i = 0; i<hashTable->size; i++)
	{
		elem = hashTable->elements[i];
		
		if(&elem->value > address)
			printf("%d: \n", i);
		
		while(elem != NULL)
		{
			printf("      ");
			printf("%s : %d\n", elem->key, elem->value);
			elem = elem->next;
		}
	}
	printf("----END----\n");
}

void freeHashTable(HashTable *hashTable) {
  // Cerinta 1
  
  	Element *free1, *free2;
  	long i;
  
  	for(i=0; i<hashTable->size; i++)
  	{
  		free1 = hashTable->elements[i];
  		
  		while(free1 != NULL)
  		{
  			free2 = free1;
  			free1 = free1->next;
  			
  			free(free2->key);
  			free(free2);
  		}
  	}
  	
  	free(hashTable->elements);
	free(hashTable);	
}


long hash1(Key word, long size) {
  // Cerinta 2
  
  long h = 0;
  
  for(long i = 0; i<strlen(word); i++)
  	 h=h*17 + word[i];
  
  return h%size;
  
}

int main(int argc, char* argv[]) {

	HashTable *hashTable;
  	FILE *f1, *f2;
  	char word[256];
  	long hashSize, common=0;

  	hashSize = atoi(argv[1]);
  	f1 = fopen(argv[2], "r");
  	f2 = fopen(argv[3], "r");

  	initHashTable(&hashTable, hashSize, &hash1);

	// Cerinta 3

	Value val;
	while(fscanf(f1, "%s", word) != EOF)
	{

  		if(exists(hashTable, word) == 0)
  			val = 1;

  		else
  		{
  			val = get(hashTable, word);
  			val++;
  		}
  		
  		put(hashTable, word, val);
	}
  
	print(hashTable);
  
	// Cerinta 4

	HashTable *hashTable2;
	initHashTable(&hashTable2, hashSize, &hash1);

	while(fscanf(f2, "%s", word) != EOF)
	{

  		if(exists(hashTable2, word) == 0)
  			val = 1;
  	
  		else
  		{
  			val = get(hashTable, word);
  			val++;
  		}
  		put(hashTable2, word, val);

	}
	
	Element* elem;
  	int i, min;
  	for(i=0; i<hashTable2->size; i++)
  	{
  		elem = hashTable2->elements[i];
  		while(elem != NULL)
  		{
  			min = -1;
  			if(exists(hashTable, elem->key))
  			{
  				min = get(hashTable2, elem->key);
  				if(get(hashTable, elem->key)<min)
  					min = get(hashTable, elem->key);
  				common = common+ min;
  			}
  			elem = elem->next;
  		}
  	}
	
	printf("Common words: %ld\n", common);

  	fclose(f1);
  	fclose(f2);
  	
  	return 0;
}
