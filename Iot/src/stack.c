#include <stack.h>
#include <stdbool.h>
#include <stdlib.h>

void init_stack(Stack *stack) {
  stack->top = NULL;
  stack->size = 0;
}

bool isEmpty(Stack *stack) { return stack->top == NULL; }

void push(Stack *stack, char *request) {
  Node *newNode = malloc(sizeof(Node));
  newNode->request = request;
  newNode->next = stack->top;
  stack->top = newNode;
  stack->size++;
}

char *top(Stack *stack) { return stack->top->request; }

void pop(Stack *stack) {
  Node *temp = stack->top;
  stack->top = stack->top->next;
  free(temp);
  stack->size--;
}

void free_stack(Stack *stack) {
  Node *temp = stack->top;
  while (temp != NULL) {
    Node *next = temp->next;
    free(temp);
    temp = next;
  }
  stack->top = NULL;
  stack->size = 0;
}
