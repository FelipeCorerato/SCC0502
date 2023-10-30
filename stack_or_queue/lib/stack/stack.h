#ifndef SCC0502_STACK_H
#define SCC0502_STACK_H

typedef struct Stack {
    int size;
    int lastIndex;
    int* array;
} Stack;

void initializeStack(Stack* stack, int size);
void push(Stack* stack, int value);
int pop(Stack* stack);
void destroyStack(Stack* stack);

#endif
