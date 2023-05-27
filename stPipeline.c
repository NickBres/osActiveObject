#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "stPipeline.h"

#define ACTIVE_OBJECTS 4

int seed = 0;
int tasks = 0;

int main(int argc, char *argv[])
{
    if (argc > 3 || argc < 2)
    {
        printf("Usage: %s <tasksNum> <seed>\n", argv[0]);
        return 1;
    }
    else
    {
        tasks = atoi(argv[1]);
    }
    if (argc == 3)
    {
        seed = atoi(argv[2]);
    }

    ActiveObjectPtr *activeObjects = (ActiveObjectPtr *)malloc(sizeof(ActiveObjectPtr) * ACTIVE_OBJECTS);
    if (activeObjects == NULL)
    {
        printf("Error: malloc failed\n");
        return 1;
    }

    printf("Creating %d handlers\n", ACTIVE_OBJECTS);
    HandlerPtr *handlers = (HandlerPtr *)malloc(sizeof(HandlerPtr) * ACTIVE_OBJECTS);
    if (handlers == NULL)
    {
        printf("Error: malloc failed\n");
        return 1;
    }
    for (int i = 0; i < ACTIVE_OBJECTS; i++)
    {
        handlers[i] = malloc(sizeof(Handler));
        if (handlers[i] == NULL)
        {
            printf("Error: malloc failed\n");
            return 1;
        }
    }
    handlers[0]->handler = func1;
    handlers[1]->handler = func2;
    handlers[2]->handler = func3;
    handlers[3]->handler = func4;

    for (int i = 0; i < ACTIVE_OBJECTS; i++)
    {
        initActiveObject(&(activeObjects[i]), tasks, NULL, handlers[i]);
    }

    for (int i = 0; i < ACTIVE_OBJECTS - 1; i++)
    {
        activeObjects[i]->pNext = activeObjects[i + 1];
    }

    for (int i = 0; i < ACTIVE_OBJECTS; i++)
    {
        startActiveObject(activeObjects[i]);
    }

    for (int i = 0; i < tasks; i++)
    {
        sleep(1);
        int num = seed ? seed + i : 0;
        enqueueActiveObject(activeObjects[0], num);
    }

    for (int i = 0; i < ACTIVE_OBJECTS; i++)
    {
        waitActiveObject(activeObjects[i]);             // block until all tasks are done
        pthread_join(activeObjects[i]->threadId, NULL); // wait for thread to terminate
        destroyActiveObject(activeObjects[i]);          // free resources
    }

    free(activeObjects);

    return 0;
}

int isPrime(unsigned int num)
{
    if (num == 0 || num == 1)
    {
        return 0;
    }
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int randomInt(int seed)
{
    if (!seed)
    {
        seed = time(0);
    }
    srand(seed);                                 // Set the seed for the random number generator
    int randomNumber = rand() % 900000 + 100000; // Generate a random number between 100000 and 999999
    return randomNumber;
}

int func1(int seed)
{
    int num = randomInt(seed);
    return num;
}

int func2(int num)
{
    printf("%d\n", num);
    if (isPrime(num))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
    num += 11;
    return num;
}

int func3(int num)
{
    printf("%d\n", num);
    if (isPrime(num))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
    num -= 13;
    return num;
}

int func4(int num)
{
    printf("%d\n", num);
    if (isPrime(num))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
    num += 2;
    printf("%d\n", num);
    return num;
}