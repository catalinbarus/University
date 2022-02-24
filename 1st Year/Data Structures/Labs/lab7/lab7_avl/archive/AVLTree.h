
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include<stdlib.h>

// An AVL tree node
typedef struct AVLNode{
	Item elem;
	int height;
	struct AVLNode *l;
	struct AVLNode *r;
	struct AVLNode *p;

}AVLNode;

typedef struct AVLTree{
	long size;
	AVLNode* root;
	AVLNode* nil;
	int (*comp)(Item a, Item b);
}AVLTree;

AVLTree* avlCreateTree(int (*comp) (Item1,Item1))
{
	AVLTree* newTree = (AVLTree*) malloc(sizeof(AVLTree));
	newTree->comp = comp;
	newTree->nil = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->nil->p = newTree->nil->l = newTree->nil->r = newTree->nil;
	newTree->nil->height = 0;
	newTree->root = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->root->p = newTree->root->l = newTree->root->r = newTree->nil;
	newTree->root->height = 0;
	newTree->size = 0;

	return newTree;
}

int avlIsEmpty(AVLTree* tree){
	return (tree->root->l == tree->nil);
}

AVLNode* avlNewNode(AVLTree* tree){
	AVLNode* newNode = (AVLNode*) malloc(sizeof(AVLNode));
	// Initialize the new node to be used in the tree
	newNode->p = newNode->r = newNode->l = tree->nil;
	newNode->height = 1;

	return newNode;
}



// A utility function to get maximum of two integers
int max(int a, int b){
	return (a > b)? a : b;
}

// A utility function to right rotate subtree rooted with y
void avlRightRotate(AVLTree *tree,  AVLNode *y){
	//TO DO HERE
	AVLNode *left, *parent;

	parent = y->p;
	left  = y->l;
	y->l = left->r;
	left->r->p = y;
	left->r = y;
	y->p =left;


	y->height = max(y->l->height, y->r->height)+1;
	left->height = max(left->l->height, y->height)+1;

	if(parent == tree->root)
		tree->root->l=left;
	
	else if(parent->elem < left->elem)
		parent->r=left;
	else
		parent->l=left;
	
	left->p=parent;	
}

// A utility function to left rotate subtree rooted with x
void avlLeftRotate(AVLTree *tree, AVLNode *x){
	//TO DO HERE
	AVLNode *right, *parent;
	
	parent=x->p;
	right=x->r;
	x->r=right->l;
	right->l->p=x;
	right->l=x;
	x->p=right;

	x->height=max(x->l->height,x->r->height)+1;
	right->height=max(right->l->height, x->height)+1;
	
	if(parent == tree->root)
		tree->root->l=right;
	
	else if(parent->elem < right->elem)
		parent->l=right;
	else
		parent->r=right;
	
	right->p=parent;
}

// Get Balance factor of node x
int avlGetBalance(AVLNode *x){
	if (x == NULL)
		return 0;
	return x->l->height - x->r->height;
}

AVLNode * avlMinimum(AVLTree* tree, AVLNode* x){
	while (x->l != tree->nil)
		x = x->l;
	return x;
}

AVLNode* avlMaximum(AVLTree* tree, AVLNode* x){
	while(x->r != tree->nil){
		x = x->r;
	}
	return x;
}



void avlInsert(struct AVLTree* tree, Item elem){
	//TO DO HERE
	
	AVLNode *node=(AVLNode*)malloc(sizeof(AVLNode));
	node->p=tree->nil;
	node->l=tree->nil;
	node->r=tree->nil;
	node->height = 1;
	node->elem = elem;
	

	if(tree->root->l != tree->nil)
	{
		AVLNode *aux = tree->root->l;
		while(aux != tree->nil)
		{
			if(elem == aux->elem) 
				return;

			if(tree->comp(elem, aux->elem) == -1) 
			{
				if (aux->l == tree->nil) 
				{
					aux->l = node;
					node->p = aux;
					break;
				}
				aux = aux->l;
			}
			else if (tree->comp(elem, aux->elem) == 1) 
			{
				if (aux->r == tree->nil) 
				{
					aux->r=node;
					node->p = aux;
					break;
				}
				aux = aux->r;
			}
		}
		tree->size++;

		AVLNode *t=node->p;
		while(t != tree->root)
		{
			t->height=max(t->l->height, t->r->height)+1;
	
			if(avlGetBalance(t) == 2)
			{
				if(tree->comp(elem, t->l->elem) == -1)
					avlRightRotate(tree, t);
				else
				{
					avlLeftRotate(tree, t->l);
					avlRightRotate(tree, t);
				}
			}
			if(avlGetBalance(t) == -2)
			{
				if(tree->comp(elem, t->r->elem) == 1)
					avlLeftRotate(tree, t);		
				else
				{
					avlRightRotate(tree, t->r);
					avlLeftRotate(tree, t);
				}
			}
			t=t->p;
		}
	}
	else 
	{
		tree->root->l=node;
		node->p=tree->root;
		tree->size++;
	}
}




void avlDeleteNode(AVLTree *tree, AVLNode* node){
	destroyElem(node->elem);
	free(node);
}


void avlDestroyTreeHelper(AVLTree* tree, AVLNode* x) {
	if (x != tree->nil) {
		avlDestroyTreeHelper(tree,x->l);
		avlDestroyTreeHelper(tree,x->r);
		avlDeleteNode(tree,x);
	}
}

void avlDestroyTree(AVLTree* tree){
	avlDestroyTreeHelper(tree, tree->root->l);
	free(tree->root);
	free(tree->nil);
	free(tree);
}

#endif /* AVLTREE_H_ */
