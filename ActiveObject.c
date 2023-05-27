#include "ActiveObject.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

void *runActiveObject(void *arg)
{
    ActiveObjectPtr pActiveObject = (ActiveObjectPtr)arg;
    if(!pActiveObject){
        printf("Error: ActiveObject is NULL\n");
        exit(1);
    }
    while (pActiveObject->isActive)
    {
        pthread_mutex_lock(&(pActiveObject->mutex));
        if (!isEmpty(pActiveObject->pQueue))
        {
            void *data = dequeue(pActiveObject->pQueue);
            pthread_mutex_unlock(&(pActiveObject->mutex));
            int result = pActiveObject->pHandler->handler((int)(intptr_t)data);

            if (pActiveObject->pNext)
            {
                enqueueActiveObject(pActiveObject->pNext, (void *)(intptr_t)result);
            }
            pActiveObject->maxTasks--;
            if (pActiveObject->maxTasks == 0)
            {
                stopActiveObject(pActiveObject);
            }
        }
        else
        {
            pthread_mutex_unlock(&(pActiveObject->mutex));
            sleep(1); // to prevent CPU 100%
        }
    }
    return NULL;
}

void initActiveObject(ActiveObjectPtr *pActiveObject, int maxTasks, ActiveObjectPtr next, HandlerPtr func)
{
    *pActiveObject = (ActiveObjectPtr)malloc(sizeof(ActiveObject));
    if (!(*pActiveObject))
    {
        printf("Error: Out of memory\n");
        exit(1);
    }
    (*pActiveObject)->maxTasks = maxTasks;
    (*pActiveObject)->isActive = 0;
    initQueue(&((*pActiveObject)->pQueue));
    (*pActiveObject)->pNext = next;
    (*pActiveObject)->pHandler = func;
    pthread_mutex_init(&((*pActiveObject)->mutex), NULL);
}

void destroyActiveObject(ActiveObjectPtr pActiveObject)
{
    pActiveObject->isActive = 0;
    destroyQueue(pActiveObject->pQueue);
    free(pActiveObject->pQueue);
    pthread_mutex_destroy(&(pActiveObject->mutex));
    pActiveObject->pHandler = NULL;
    pActiveObject->pNext = NULL;
    free(pActiveObject);
}

void startActiveObject(ActiveObjectPtr pActiveObject)
{
    if (!pActiveObject)
    {
        printf("Error: ActiveObject is NULL\n");
        exit(1);
    }
    pActiveObject->isActive = 1;
    pthread_t threadId;
    pthread_create(&threadId, NULL, runActiveObject, pActiveObject);
}

void stopActiveObject(ActiveObjectPtr pActiveObject)
{
    pthread_mutex_lock(&(pActiveObject->mutex));
    pActiveObject->isActive = 0;
    pthread_mutex_unlock(&(pActiveObject->mutex));
}

void enqueueActiveObject(ActiveObjectPtr pActiveObject, void *data)
{
    pthread_mutex_lock(&(pActiveObject->mutex));
    enqueue(pActiveObject->pQueue, data);
    pthread_mutex_unlock(&(pActiveObject->mutex));
}

void waitActiveObject(ActiveObjectPtr pActiveObject)
{
    while (pActiveObject->isActive || !isEmpty(pActiveObject->pQueue))
    {
        sleep(1);
    }
}
