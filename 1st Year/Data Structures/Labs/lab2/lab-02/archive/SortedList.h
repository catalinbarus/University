#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct SortedList {
  T value;
  struct SortedList* next;
} SortedList;

// TODO : Cerința 1 & Cerința 2

void init(SortedList **list)
{
	*list=NULL;
}

int isEmpty(SortedList *list)
{
	if(list==NULL)
		return 1;
	else
		return 0;
}

int contains(SortedList *list, T elem)
{
	while(list!=NULL)
	{
		if(list->value==elem)
			return 1;
		list=list->next;
	}
	return 0;
}

void insert(SortedList **list, const T newElem)
{
	SortedList* node = (SortedList*)malloc(sizeof(SortedList));
	if (!node)
		return;	
    	node->value = newElem;
	node->next = NULL;
    	if (*list == NULL)
		*list = node; 
	else
	{
		SortedList *prev, *current;
		prev = NULL;
		current = *list;
		while ((current != NULL) && (current->value < newElem)) 
		{
			prev = current;
			current = current->next;
		}
		if (prev != NULL) 
		{
			prev->next = node;
			node->next = current;
		}
		else
		{
			node->next = current;
			*list = node;
		}
	}
}

void deleteOnce(SortedList **list, T elem)
{
	if (*list == NULL) 
		return;
	SortedList *prev, *current;
	prev = NULL;
	current = *list;
	if (contains(*list, elem)) 
	{
		if (current->value == elem) 
		{
			*list = current->next;
			free(current);
		}
		else
		{
			while ((current != NULL) && (current->value < elem))
			{
				prev = current;
				current = current->next;
			}
			prev->next = current->next;
			free(current);
		}
	}
	else return;
		
}

long length(SortedList *list)
{
	long lung=0;
	SortedList *current;
	current=list;
	while(current != NULL)
	{
		lung++;
		current=current->next;
	}
	return lung;
}

int getNth(SortedList *list, int poz)
{
	int i=0;
	while(list!=NULL)
	{
		i++;
		if(i==poz)
			return list->value;
		list=list->next;
	}
}

void freeSortedList(SortedList **list)
{
	SortedList *current = *list;
	SortedList *current_copy;
	while (current != NULL)
	{
		current_copy = current;
		current = current->next;
		free(current_copy);
	}
}
	
		
	
		

#endif
