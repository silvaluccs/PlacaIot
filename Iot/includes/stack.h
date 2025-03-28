#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct Node {
    char* request;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
    int size;
} Stack;

void init_stack(Stack* stack);
bool isEmpty(Stack* stack);
void push(Stack* stack, char* request);
void pop(Stack* stack);
void free_stack(Stack* stack);

#endif // ! STACK_H
