/*library that implements a stack with 2 arrays*/
#ifndef STACK_H
#define STACK_H

typedef struct{
    unsigned int size;
    int top;
    unsigned int *r, *c;
} stack_t;

stack_t *createStack(unsigned int row, unsigned int column);

int isFull(stack_t *s);

int isEmpty(stack_t *s);

void stackUp(stack_t *s, unsigned int x, unsigned int y);

void unstack(stack_t *s);

void peek(stack_t *s);

#endif