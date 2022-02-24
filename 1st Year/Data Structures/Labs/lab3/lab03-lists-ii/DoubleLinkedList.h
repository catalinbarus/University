#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void){
	// TODO: Cerinta 1a
	List* elem=(List*)malloc(sizeof(List));
	elem->first=NULL;
	elem->last=NULL; 
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	// TODO: Cerinta 1b
	if(list == NULL || list->first == NULL)
		return 1;
	else
		return 0;
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	// TDOO: Cerinta 1c
	if(list->first == NULL || list == NULL)
		return 0;
	else
	{
		ListNode *poz=list->first;
		while(poz != NULL)
		{
			if(poz->elem == elem)
				return 1;
			poz=poz->next;
		}
	}
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */

void insertAt(List* list, Item elem, int pos){

	ListNode *tmp=NULL, *start=list->first, *end=list->last;

	if(list == NULL) return;
	if(pos<0 || pos>length(list)) return;
	if(list->first == NULL && pos != 0) return;

	ListNode *newelem=(ListNode*)malloc(sizeof(ListNode));
	newelem->elem=elem;

	if(pos == 0 && list->first==NULL)
	{
		list->first=newelem;
		list->last=newelem;
		newelem->next=NULL;
		newelem->prev=NULL;
		return;
	}
	if(pos == 0 && list->first!=NULL)
	{
		newelem->next=start;
		newelem->prev=NULL;
		start->prev=newelem;
		list->first=newelem;
		return;
	}	
	if(pos == length(list))
	{
		end->next=newelem;
		newelem->next=NULL;
		newelem->prev=end;
		list->last=newelem;
		return;
	}
	start=list->first;
	int count=0;
	while(count != pos)
	{
		tmp=start;
		start=start->next;
		count++;
	}
	tmp->next=newelem;
	newelem->prev=tmp;
	newelem->next=start;
	start->prev=newelem;
	return;
	//else return;

	// TODO: Cerinta 1d
}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance from a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem){
	// Guard against young player errors
	if(list == NULL || list->first==NULL) return;
	if(contains(list,elem)==0) return;
	
	ListNode *poz=list->first;
	ListNode *tmp=NULL;
	if(poz->elem==elem && poz->next==NULL)
	{
		list->first=NULL;
		list->last=NULL;
		free(poz);
		return;
	}
	if(poz->elem==elem && poz->next!=NULL)
	{
		tmp=poz->next;
		tmp->prev=NULL;
		list->first=tmp;
		free(poz);
		return;
	}
	
	while(poz!=NULL && poz->elem!=elem)
	{
		tmp=poz;
		poz=poz->next;
	}
	
	if(poz->next==NULL)
	{
		tmp->next=NULL;
		list->last=tmp;
		free(poz);
		return;
	}
	else
	{
		tmp->next=poz->next;
		free(poz);
		return;
	}
		    
	    //TODO: Cerinta 1e
	//TODO: Cerinta 1e
}
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list){
	// Guard against young player errors
	if(list == NULL) return 0;
	ListNode *poz=list->first;
	int lung=0;
	while(poz != NULL)
	{
		lung++;
		poz=poz->next;
	}
	return lung;
	// TODO: Cerinta 1f
}
// -----------------------------------------------------------------------------



/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
void destroyList(List* list){
	// Guard against young player errors
	if(list == NULL) return;

	//TODO: Cerinta 1g
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
