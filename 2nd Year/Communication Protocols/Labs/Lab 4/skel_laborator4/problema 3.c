
#include <stdio.h>
#include <stdlib.h>

struct node {
    int ora;
    int min;
    int sec;
    struct node *left, *right;
};

struct QNode {
    int ora;
    int min;
    int sec;
    struct QNode *next;
    struct QNode *prev;
};

struct Queue {
    struct QNode *front, *rear;
};

struct QNode *newQueueNode(int ora, int min, int sec) {
    struct QNode *temp = (struct QNode *) malloc(sizeof(struct QNode));
    temp->ora = ora;
    temp->min = min;
    temp->sec = sec;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

struct Queue *createQueue() {
    struct Queue *q = (struct Queue *) malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enQueue(struct Queue *q, int ora, int min, int sec) {
    struct QNode *temp = newQueueNode(ora, min, sec);

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        q->front->next = q->rear;
        q->rear->prev = q->front;
        return;
    }
    q->rear->next = temp;
    temp->prev = q->rear;
    q->rear = temp;
}

void deQueue(struct Queue *q) {
    if (q->front == NULL)
        return;

    struct QNode *temp = q->front;

    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}

QNode *top(struct Queue *q) {
    return q->front;
}

bool isEmpty(struct Queue *q) {
    if (q->front == NULL) {
        return true;
    } else {
        return false;
    }
}

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
    struct Queue *q = createQueue();
    while (true) {
        int ora, minut, secunda;
        scanf("%d %d %d", &ora, &minut, &secunda);
        if (ora == 0 && minut == 0 && secunda == 0) {
            break;
        }
        enQueue(q, ora, minut, secunda);

    }
    QNode *node = top(q);
    if (!isEmpty(q)) {
        root = insert(root, node->ora, node->min, node->sec);
        deQueue(q);
    }
    while (!isEmpty(q)) {
        node = top(q);
        insert(root, node->ora, node->min, node->sec);
        deQueue(q);
    }
    inorder(root);

    return 0;
}