#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>



typedef struct StackNode{
	Item elem;
	struct StackNode *next;
}StackNode;

typedef StackNode TCelSt; // Redenumirea unui nod la notatiile din curs 
typedef StackNode *ACelSt; // Redenumirea unui pointer la nod la notatiile din curs

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
}Stack;

typedef Stack TStiva; // Redenumirea stivei la notatiile din curs
typedef Stack *ASt;//  // Redenumirea unui pointer la stiva la notatiile din curs

Stack* createStack(void){
	// TODO: Cerinta 1
	Stack *stack=(Stack*)malloc(sizeof(Stack));
	if(!stack)
		return NULL;
	stack->head=NULL;
	stack->size=0;
	//return NULL;
}

int isStackEmpty(Stack* stack){
	// TODO: Cerinta 1
	if(stack->head == NULL)
		return 1;
	else
		return 0;
}

void push(Stack *stack, Item elem){
	// TODO: Cerinta 1
	if(stack == NULL) return;
	StackNode *node=(StackNode*)malloc(sizeof(StackNode));
	node->elem=elem;
	node->next=NULL;
	node->next=stack->head;
	stack->head=node;
	stack->size++;
}

Item top(Stack *stack){	
	// TODO: Cerinta 1
	if(stack == NULL)
		return -1;
	return stack->head;
} 

void pop(Stack *stack){
	// TODO: Cerinta 1
	StackNode *tmp;
	tmp=stack->head;
	stack->head=stack->head->next;
	stack->size--;
	free(tmp);
}

void destroyStack(Stack *stack){
	// TODO: Cerinta 1
	while(isStackEmpty(stack) == 0) 
		pop(stack); 
	free(stack);
}

#endif 
