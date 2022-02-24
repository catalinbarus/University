/*
 * BSTList.c
 *
 *  Created on: Apr 2, 2016
 *      Author: dan
 */

typedef long Item;
#include "BST.h"
typedef BSTNode* Item2;
#include "List.h"
#include "Queue.h"


BSTree* buildTree(Item *array, long len);

// -----------------------------------------------------------------------------
List* bstToList(BSTree* tree){ 
	//TODO: Cerinta 4
	Queue *q;
	List *l;
	l = createList();
	initQueue(q);
	enqueue(q,tree -> root ->l);
	while(isEmptyQueue(q))
	{
		listPushBack(q,q -> front -> value);
		if(front(q) -> l !=  tree ->nil)
			enqueue(q,front(q)-> l);
		if(front(q) -> r !=  tree ->nil)
			enqueue(q,front(q)-> r);
		dequeue(q);
	}
	destroyQueue(q);
	return l;
}
void printList(List* list){
	//TODO: Cerinta 4
	ListNode *aux;
	aux = list -> head;
	while(aux != NULL){
		printf("%ld\n",aux -> elem);
	aux = aux -> next;
	}
}
// -----------------------------------------------------------------------------

int main(void){
	Item array[] = {5,3,2,4,7,6,8};

	BSTree *tree = buildTree(array, sizeof(array)/sizeof(Item));

	List *list=bstToList(tree);	

	printList(list);

	destroyTree(tree);

	return 0;
}

BSTree* buildTree(Item *array, long len){
	BSTree* newTree = createTree();
	for(int i = 0; i < len; i++){
		insert(newTree,array[i]);
	}
	return newTree;
}
