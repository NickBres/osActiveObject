#ifndef ACTIVEOBJECT_H
#define ACTIVEOBJECT_H

#include "queue.h"
#include <pthread.h>

typedef struct{
    int (*handler)(int num);
} Handler, *HandlerPtr;

typedef struct ActiveObject ActiveObject, *ActiveObjectPtr;

struct ActiveObject
{
    int isActive;
    int maxTasks;
    QueuePtr pQueue;
    HandlerPtr pHandler;
    ActiveObjectPtr pNext;
    pthread_mutex_t mutex;
    pthread_t threadId;
};

void initActiveObject(ActiveObjectPtr* pActiveObject,int maxTasks,ActiveObjectPtr next, HandlerPtr func); // constructor
void destroyActiveObject(ActiveObjectPtr pActiveObject); // destructor
void startActiveObject(ActiveObjectPtr pActiveObject); // start the thread
void* runActiveObject(void *pArg); // thread functions
void stopActiveObject(ActiveObjectPtr pActiveObject); // stop the thread
void enqueueActiveObject(ActiveObjectPtr pActiveObject, void *data); // add new data to the queue
void waitActiveObject(ActiveObjectPtr pActiveObject); // wait for the thread to finish


#endif // ACTIVEOBJECT_H