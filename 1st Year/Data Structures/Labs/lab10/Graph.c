#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphL* createGraphAdjList(int numberOfNodes) {
	//TODO: 1
	TGraphL*graph=(TGraphL*)malloc(sizeof(TGraphL));
	
	if(graph == NULL)
		return NULL;
	
	graph->nn=numberOfNodes;
	graph->adl=calloc(numberOfNodes, sizeof(TNode));
	return graph;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {
	//TODO: 1
	TNode* aux1=(TNode*)malloc(sizeof(TNode));
	TNode* aux2=(TNode*)malloc(sizeof(TNode));
	aux1->v=v1;
	aux2->v=v2;
	aux2->next=graph->adl[v1];
	graph->adl[v1]=aux2;
	aux1->next=graph->adl[v2];
	graph->adl[v2]=aux1;
}

List* dfsIterative(TGraphL* graph, int s) {
	//TODO: 2
	Stack* stack=createStack();
	List* list=createList();
	int *vizit=malloc(graph->nn*sizeof(int));
	vizit[s]++;
	push(stack, s);
	while(!isStackEmpty(stack))
	{
		int tmp=top(stack);
		vizit[tmp]=1;
		pop(stack);
		TNode* vecin=graph->adl[tmp];
		while(vecin)
		{
			if(vizit[vecin->v] == 0)
			{
				push(stack, vecin->v);
				vizit[vecin->v]++;
			}
			vecin=vecin->next;
		}
		enqueue(list, tmp);
	}
	free(vizit);
	destroyStack(stack);
	return list;
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
	//TODO: 3
	visited[s]=1;
	enqueue(path, s);
	TNode* vecin=graph->adl[s];
	while(vecin)
	{
		if(visited[vecin->v] == 0)
		dfsRecHelper(graph, visited, path, vecin->v);
		vecin=vecin->next;
	}
}

List* dfsRecursive(TGraphL* graph, int s) {
	// TODO 3
	List* list=createList();
	int* vizit=(int*)malloc(graph->nn*sizeof(int));
	int i;
	for(i=0; i<graph->nn; i++)
		vizit[i]=0;
	dfsRecHelper(graph, vizit, list, s);
	free(vizit);
	return list;
}

List* bfs(TGraphL* graph, int s){
	// TODO: 4
	Queue *q=createQueue();
	List* list=createList();
	int *vizit=malloc(graph->nn*sizeof(int));
	int i;
	for(i=0; i<graph->nn; i++)
		vizit[i]=0;
	vizit[s]++;
	enqueue(q, s);
	while(!isQueueEmpty(q))
	{
		int aux=front(q);
		dequeue(q);
		vizit[aux]=1;
		TNode* vecin=graph->adl[aux];
		while(vecin)
		{
			if(vizit[vecin->v] == 0)
			{
				enqueue(q, vecin->v);
				vizit[vecin->v]++;
			}
			vecin=vecin->next;
		}
		enqueue(list, aux);
	}
	free(vizit);
	destroyQueue(q);
	return list;
}


void destroyGraphAdjList(TGraphL* graph){
	// TODO: 5
	for (int i=0; i<graph->nn; i++)
	{	
		TNode* parc=graph->adl[i];
		while(parc != NULL)
		{
			TNode *aux;
			aux=parc;
			parc=parc->next;
			free(aux);
		}
	}
	free(graph->adl);
	free(graph);
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
	while(it != NULL && it->v != v2){
		prev = it;
		it = it->next;
	}

	if(it == NULL)return;

	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while(it != NULL && it->v != v1){
		prev = it;
		it = it->next;
	}
	if(it == NULL) return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL* graph, int v){
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
