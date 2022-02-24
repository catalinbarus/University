#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef QueueNode TcelQ;
typedef QueueNode *ACelQ;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

typedef Queue TCoada;
typedef Queue *AQ;


Queue* createQueue(void){
	// TODO: Cerinta 2
	Queue *queue=(Queue*)malloc(sizeof(Queue));
	if(!queue)
		return NULL;
	queue->front=NULL;
	queue->rear=NULL;
	queue->size=0;
} 

int isQueueEmpty(Queue *q){
	// TODO: Cerinta 2
	if(q->front==NULL || q->rear==NULL)
		return 1;
	else
		return 0;
}

void enqueue(Queue *q, Item elem){
	// TODO: Cerinta 2
	if(q == NULL) return;
	QueueNode *node=(QueueNode*)malloc(sizeof(QueueNode));
	node->elem=elem;
	if(isQueueEmpty(q)==1)
	{
		q->front=node;
		q->rear=node;
	}
	else
	{
		q->rear->next=node;
		q->rear=node;
	}
	q->size++;
	
}

Item front(Queue* q){
	// TODO: Cerinta 2
	if(q == NULL)
		return -1;
	return q->front->elem;
}

void dequeue(Queue* q){
	// TODO: Cerinta 2
	QueueNode *tmp;
	if(isQueueEmpty(q)==1) return;
	if(q->front->next == NULL)
	{
		q->front=NULL;
		q->rear=NULL;
		q->size--;
		return;
	}
	else
	{
		tmp=q->front;
		q->front=q->front->next;
		q->size--;
		free(tmp);
		return;
	}

}

void destroyQueue(Queue *q){
	// TODO: Cerinta 2
	while(isQueueEmpty(q) == 0)
		dequeue(q);
	free(q);
}

#endif
