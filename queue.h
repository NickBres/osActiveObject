#ifndef QUEUE_H
#define QUEUE_H

typedef struct node* NodePtr;

typedef struct node
{
    void* data;
    NodePtr next;
    NodePtr prev;
}Node;


typedef struct queue{
    NodePtr front;
    NodePtr rear;
} Queue, *QueuePtr;

NodePtr createNode(void* data);

void initQueue(QueuePtr *queue);
void* dequeue(QueuePtr queue);
void enqueue(QueuePtr queue, void* data);
void destroyQueue(QueuePtr queue);
int isEmpty(QueuePtr queue);


#endif /* QUEUE_H */
