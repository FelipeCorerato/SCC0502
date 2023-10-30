#include <stdlib.h>

#include "queue.h"

void initializeQueue(Queue* queue, int size) {
    queue->size = size;
    queue->array = (int*) malloc(size * sizeof(int));
    queue->lastIndex = -1;
}

void enqueue(Queue* queue, int value) {
    queue->array[queue->lastIndex + 1] = value;

    queue->lastIndex = queue->lastIndex + 1;
    queue->size = queue->size + 1;
}

int dequeue(Queue* queue) {
    int ret = queue->array[0];

    for (int i = 0; i <= queue->lastIndex; i++) {
        queue->array[i] = queue->array[i+1];
    }

    queue->lastIndex = queue->lastIndex - 1;
    queue->size = queue->size - 1;

    return ret;
}

void destroyQueue(Queue* queue) {
    free(queue->array);
}