#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap{
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;


PriQueue* makeQueue(int maxHeapSize){
	//TODO:
	PriQueue *heap;
	
	heap=(PriQueue*)malloc(sizeof(PriQueue));
	heap->maxHeapSize=maxHeapSize;
	heap->size=0;
	heap->elem=(ItemType*)malloc(maxHeapSize*sizeof(ItemType));

	return heap;
	return NULL;
}

int getLeftChild(int i){
	//TODO:
	return 2*i+1;;
}

int getRightChild(int i) {
	//TODO:
	return 2*i+2;
}

int getParent(int i) {
	//TODO:
	return (i-1)/2;
}

ItemType getMax(APriQueue h) {
	//TODO:
	if(h != NULL && h->elem != NULL)
		return h->elem[0];
}

void siftUp(APriQueue h, int idx) {
	//TODO:
	int parent;
	parent=getParent(idx);

	while (parent >= 0 && h->elem[parent].prior < h->elem[idx].prior)
	{
		ItemType tmp=h->elem[parent];
		h->elem[parent]=h->elem[idx];
		h->elem[idx]=tmp;
		idx=parent;
		parent=getParent(idx);
	}
}


void insert(PriQueue *h, ItemType x) {
	//TODO:
	if (h == NULL) return;


	if (h->size == h->maxHeapSize)
	{
		h->maxHeapSize=h->maxHeapSize*2;
		h->elem=realloc(h->elem, h->maxHeapSize*sizeof(ItemType));
	}

	h->elem[h->size] = x;
	siftUp(h, h->size);
	h->size++;
}

void siftDown(APriQueue h, int idx){
	//TODO:
	int lefty;
	while(getLeftChild(idx) < h->size)
	{
		lefty=getLeftChild(idx);

		if(lefty < h->size && h->elem[lefty].prior < h->elem[lefty+1].prior)
			lefty++;

		if(h->elem[idx].prior > h->elem[lefty].prior)
			break;

		ItemType aux;
		aux=h->elem[idx];
		h->elem[idx]=h->elem[lefty];
		h->elem[lefty]=aux;
		idx=lefty;
	}
}

void removeMax(APriQueue h) {
	//TODO:
	h->elem[0]=h->elem[h->size-1];
	h->size--;
	siftDown(h, 0);
}

void freeQueue(APriQueue h){
	// TODO:
	free(h->elem);
	free(h);
}

#endif

