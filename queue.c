#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

NodePtr createNode(void* data) {
    NodePtr newNode = (NodePtr)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void initQueue(QueuePtr *queue) {
    *queue = (QueuePtr)malloc(sizeof(Queue));
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
}

void* dequeue(QueuePtr queue) {
    if (queue->front == NULL) {
        printf("Error: Queue is empty\n");
        return NULL;
    }

    NodePtr frontNode = queue->front;
    void* data = frontNode->data;
    
    queue->front = frontNode->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    } else {
        queue->front->prev = NULL;
    }

    free(frontNode);
    return data;
}

void enqueue(QueuePtr queue, void* data) {
    NodePtr newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = newNode;
    } else {
        queue->rear->next = newNode;
        newNode->prev = queue->rear;
    }
    queue->rear = newNode;
}

void destroyQueue(QueuePtr queue) {
    NodePtr current = queue->front;
    while (current != NULL) {
        NodePtr next = current->next;
        free(current);
        current = next;
    }
    queue->front = NULL;
    queue->rear = NULL;
}

int isEmpty(QueuePtr queue) {
    return queue->front == NULL;
}