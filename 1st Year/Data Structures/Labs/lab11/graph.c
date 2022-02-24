#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1)*sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 0; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	free(G->adl);
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
 TNode *t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}


void dijkstra(TGraphL G, int s)
{
    int d[G.nn], i;
	d[s]=0;
	for (i=0; i<G.nn; i++)
	{
		if(i != s) 
			d[i]=INT_MAX;
	}

	MinHeap *heap=newQueue(G.nn);
	for (i=0; i<G.nn; i++)
	{
		if(i != s)
			insert(heap, i, INT_MAX);
		else 
			insert(heap, i, 0);
	}
	SiftUp(heap, s, 0);
	while(!isEmpty(heap))
	{
		MinHeapNode *u=removeMin(heap);
		int idx=u->v;
		TNode *nod=G.adl[idx];
		while(nod)
		{
			if(isInMinHeap(heap, nod->v))
			{
				if(d[idx] + nod->c < d[nod->v])
				{
					d[nod->v]=d[idx] + nod->c;
					SiftUp(heap, nod->v, d[nod->v]);
				}
			}
			nod=nod->next;
		}
		free(nod);
    	free(u);
	}
	printf("\n");
	printf("Varf   Drum minim\n");
	for (i = 0; i < G.nn; i++)
		printf("  %d        %d\n", i, d[i]);
	printf("\n");
	
	free(heap->elem);
    free(heap->pos);
    heap->size=0;
    free(heap);
}

void Prim(TGraphL G)
{
    int d[G.nn], i, parent[G.nn];
	int s=0;
	d[s] = 0;
	parent[s]=0;
	for (i=0; i<G.nn; i++)
	{
		if(i != s) 
			d[i]=INT_MAX;
	}

	MinHeap *heap=newQueue(G.nn);
	for (i=0; i<G.nn; i++)
	{
		if (i != s)
			insert(heap, i, INT_MAX);
		else 
			insert(heap, i, 0);
	}
	SiftUp(heap, s, 0);
	while (!isEmpty(heap))
	{
		MinHeapNode *u=removeMin(heap);
		int idx=u->v;
		TNode *nod=G.adl[idx];
		while(nod)
		{
			if (isInMinHeap(heap, nod->v))
				if (nod->c < d[nod->v])
				{
					d[nod->v]=nod->c;
					parent[nod->v]=idx;
					SiftUp(heap, nod->v, d[nod->v]);
				}
			nod=nod->next;
		}
		free(u);
    	free(nod);
	}
	printf("Parinte   Varf\n");
	for (i = 1; i < G.nn; i++)
		printf("   %d        %d\n", parent[i], i);
		
	free(heap->elem);
    free(heap->pos);
    free(heap);
}


int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    printf("%d : ", i);
    for(t = G.adl[i]; t != NULL; t = t->next)
    printf("%d ",t->v);
    printf("\n");
	}
	dijkstra(G,0);
	Prim(G);
	free_list(&G);

	return 0;
}
