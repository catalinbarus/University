#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdio.h>                                          // needed for printf
#include <stdlib.h>                           // needed for alloc, realloc, free

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

/*
  OrderedSet represents a set with elements of type T stored in memory
  in an ordered fashion.
*/

typedef struct OrderedSet {
  T* elements;                    // pointer to where the elements are in memory
  long size;                                // the number of elements in the set
  long capacity;                      // the current capacity (allocated memory)
} OrderedSet;

// -----------------------------------------------------------------------------

/*
  Function that creates an OrderedSet with elements of type T with a given
  initial capacity.
*/

OrderedSet* createOrderedSet(long initialCapacity) {

  OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

  newSet->size = 0;                        // initially, the set is empty
  newSet->capacity = initialCapacity;
  newSet->elements = (T*) malloc(initialCapacity * sizeof(T));

  return newSet;
}

// -----------------------------------------------------------------------------

/*
  Function that checks if an element exists in a given set. As the
  elements of the set are ordered in memory, this function uses binary
  search.

  Function returns 1 if the given element exists in the set, and 0
  otherwise.
*/

int contains(OrderedSet* set, const T element) {
  // TODO : Cerința 2
	int i;
	for(i=0; i<set->size; i++)
		if(element==set->elements[i])
			return 1;
  return 0;
}

// -----------------------------------------------------------------------------

/*
  Function that adds a new element to a set. If the element was
  already in the set, nothing changes. Otherwise, the element is added
  to the set. In the end, the elements must be in ascending order.
*/

void add(OrderedSet* set, const T newElement) {
  // TODO : Cerința 2
	int i;
	T aux;
	if(contains(set, newElement)==0)
	{
		if(set->size==set->capacity)
		{
			realloc(set->elements, set->capacity*2);
			set->capacity=set->capacity*2;
		}
		set->elements[set->size]=newElement;
		set->size++;
		for(i=set->size-1; i>=0; i--)
			if(set->elements[i]<set->elements[i-1])
			{
				aux=set->elements[i];
				set->elements[i]=set->elements[i-1];
				set->elements[i-1]=aux;
			}	
	}
	
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the union of
  the two
*/

OrderedSet* unionOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  // TODO : Cerința 3
	OrderedSet* newSet = createOrderedSet(s1->size+s2->size);
	int i;
	for(i=0; i<s2->size; i++)
		add(newSet, s2->elements[i]);
	for(i=0; i<s1->size; i++)
		if(contains(newSet, s1->elements[i])==0)
			add(newSet, s1->elements[i]);
	return newSet;
  //return createOrderedSet(1);
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the
  intersection of the two
*/

OrderedSet* intersectOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  // TODO : Cerința 3
	OrderedSet *newSet = createOrderedSet(s1->size+s2->size);
	int i;
	for(i=0; i<s2->size; i++)
		if(contains(s1, s2->elements[i])==1)
			add(newSet, s2->elements[i]);
	return newSet;
}


// -----------------------------------------------------------------------------

#endif
