#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

typedef struct MinHeapNode
{
    int  v;
    int d;
} MinHeapNode;


typedef struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **elem;
} MinHeap;


int getLeftChild(int i) {
    return 2 * i + 1;
}

int getRightChild(int i) {
    return 2 * i + 2;
}

int getParent(int i) {
    return floor((i - 1) / 2);
}

MinHeapNode* newNode(int v, int d)
{
    MinHeapNode* n =(MinHeapNode*) malloc(sizeof(MinHeapNode));
    n->v = v;
    n->d = d;
    return n;
}

MinHeap* newQueue(int capacity)
{
    MinHeap* h =(MinHeap*) malloc(sizeof(MinHeap));
    h->pos = (int *)malloc(capacity * sizeof(int));
    h->size = 0;
    h->capacity = capacity;
    h->elem =(MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*));
    return h;
}

void swap(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void SiftDown(MinHeap* h, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < h->size && h->elem[left]->d < h->elem[smallest]->d )
      smallest = left;

    if (right < h->size && h->elem[right]->d < h->elem[smallest]->d )
      smallest = right;

    if (smallest != idx)
    {
        MinHeapNode *a = h->elem[smallest];
        MinHeapNode *b = h->elem[idx];
        h->pos[a->v] = idx;
        h->pos[b->v] = smallest;
        swap(&h->elem[smallest], &h->elem[idx]);
        SiftDown(h, smallest);
    }
}

int isEmpty(MinHeap* h)
{
    return h->size == 0;
}

MinHeapNode* removeMin(MinHeap* h)
{
    MinHeapNode *min = h->elem[0];
    MinHeapNode *last = h->elem[h->size - 1];

    /* Remove the last elem from the vector. */
    h->size--;

    /* Set latest elem as the first and call heapify downwards. */
    h->elem[0] = last;
    SiftDown(h, 0);

    return min;
}

void SiftUp(MinHeap* h, int v, int d)
{
    int i, idx = -1;
    for (i = 0; i < h->size; i++){
        if (h->elem[i]->v == v && idx == -1){
            idx = i;
            h->elem[i]->d = d;
        }
    }

    int parent = getParent(idx);

    while (parent >= 0 && h->elem[parent]->d > h->elem[idx]->d) 
    {
        swap(h->elem + parent, h->elem + idx);
        idx = parent;
        parent = getParent(idx);
    }
}

int isInMinHeap(MinHeap *h, int v)
{
   int i;
  for (i = 0; i < h->size; i++)
  {
      if (h->elem[i]->v == v) return 1;
  }
  return 0;
}

void insert(MinHeap * h, int v, int d) {
  if(h->size == h->capacity) 
  {
 		h->capacity=h->capacity * 2;
    	h->elem=realloc(h->elem, h->capacity * sizeof(MinHeapNode));
  }
  
  h->elem[h->size]=newNode(v, d);
  h->size++;
  SiftUp(h, v, d);
} 

#endif

