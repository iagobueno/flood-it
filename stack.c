#include "stack.h"
#include <stdlib.h>

stack_t *createStack(unsigned int row, unsigned int column){
    stack_t *s;
    s = malloc(sizeof(stack_t));
    s->r = malloc(row * column * sizeof(unsigned int));
    s->c = malloc(row * column * sizeof(unsigned int));
    s->size = row * column;
    s->top = -1;

    return s;
}

int isFull(stack_t *s){
    if(s->top == s->size - 1)
        return 1;
    return 0;
}

int isEmpty(stack_t *s){
    if(s->top == - 1)
        return 1;
    return 0;
}

void stackUp(stack_t *s, unsigned int x, unsigned int y){
    if(isFull(s))
        return;

    s->top++;
    (s->r)[s->top] = x;
    (s->c)[s->top] = y;
}

void unstack(stack_t *s){
    if(isEmpty(s))
        return;

    s->top--;
}

void peek(stack_t *s){
    if(isEmpty(s))
        return;

}