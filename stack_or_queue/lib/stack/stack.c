#include <stdlib.h>

#include "stack.h"

void initializeStack(Stack* stack, int size) {
    stack->size = size;
    stack->array = (int*) malloc(size * sizeof(int));
    stack->lastIndex = -1;
}

void push(Stack* stack, int value) {
    stack->array[stack->lastIndex + 1] = value;

    stack->lastIndex = stack->lastIndex + 1;
    stack->size = stack->size + 1;
}

int pop(Stack* stack) {
    int ret = stack->array[stack->lastIndex];

    stack->array[stack->lastIndex] = 0;

    stack->lastIndex = stack->lastIndex - 1;
    stack->size = stack->size - 1;

    return ret;
}

void destroyStack(Stack* stack) {
    free(stack->array);
}