
#include <stdio.h>
#include <stdlib.h>

struct node {
    int ora;
    int min;
    int sec;
    struct node *left, *right;
};


struct node *newNode(int ora, int min, int sec) {
    struct node *temp
            = (struct node *) malloc(sizeof(struct node));
    temp->ora = ora;
    temp->min = min;
    temp->sec = sec;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Ora:%d Minutul:%d Secunda %d \n", root->ora, root->min, root->min);
        inorder(root->right);
    }
}

struct node *insert(struct node *node, int ora, int min, int sec) {
    if (node == NULL)
        return newNode(ora, min, sec);
    int node_hour = (node->ora * 3600) + (node->min * 60) + node->sec;
    int new_hour = (ora * 3600) + (min * 60) + sec;
    if (new_hour < node_hour)
        node->left = insert(node->left, ora, min, sec);
    else if (new_hour > node_hour)
        node->right = insert(node->right, ora, min, sec);

    return node;
}


int main() {
    struct node *root = NULL;
    root = insert(root, 1, 20, 30);
    insert(root, 2, 40, 12);
    insert(root, 3, 15, 45);
    insert(root, 1, 15, 12);
    insert(root, 1, 20, 21);
    insert(root, 2, 30, 43);
    insert(root, 5, 2, 5);
    inorder(root);

    return 0;
}