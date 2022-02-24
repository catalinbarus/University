#ifndef TREE_H_D
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct Link
  {
    Item  elem;
    struct Link *l;
    struct Link *r;
  } TreeNode;



void Init(TreeNode **t, Item x)
{
	TreeNode *node=(TreeNode*)malloc(sizeof(TreeNode));
	node->l=NULL;
	node->r=NULL;
	node->elem=x;  
}

void Insert(TreeNode **t, Item x)
{
	TreeNode *tmp = NULL;
	if(!(*t)) 
	{
		tmp = (TreeNode *)malloc(sizeof(TreeNode));
		tmp->l = NULL;
		tmp->r = NULL;
		tmp->elem = x;
		*t = tmp;
		return;
	}

	if(x < (*t)->elem) 
		Insert(&(*t)->l, x);
	else if(x > (*t)->elem)
		Insert(&(*t)->r, x);
}

void vizit(TreeNode *t)
{
	printf("%d ", t->elem);
}

void PrintPostorder(TreeNode *t)
{
	if(t == NULL) return;
	PrintPostorder(t->l);
	PrintPostorder(t->r);
	vizit(t);
	
}

void PrintPreorder(TreeNode *t)
{
	if(t == NULL) return;
	vizit(t);
	PrintPreorder(t->l);
	PrintPreorder(t->r);

}

void PrintInorder(TreeNode *t)
{
	if(t == NULL) return;
	PrintInorder(t->l);
	vizit(t);
	PrintInorder(t->r);
}

void Free(TreeNode **t)
{
	if((*t) == NULL) return;

	Free(&(*t)->l);
	Free(&(*t)->r);
	
	free((*t));
}

int Size(TreeNode* t)
{
	if(t == NULL)
		return 0;
	else
		return(Size(t->l) + 1 + Size(t->r));
}

int maxDepth(TreeNode *t)
{
	if(t == NULL)
		return 0;

	int leftdepth, rightdepth;
	leftdepth=maxDepth(t->l);
	rightdepth=maxDepth(t->r);
	
	if(leftdepth > rightdepth)
		return leftdepth+1;
	else
		return rightdepth+1;
}

#endif // LINKEDSTACK_H_INCLUDED
