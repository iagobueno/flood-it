/*library that is responsible for basic game structures*/
#ifndef GAME_H
#define GAME_H
#include "stack.h"

typedef struct{
    unsigned int row, column, color, status;
    unsigned int **board;
} game_t;

#define SHUTDOWN 0
#define RUNNING 1
#define RIGHT 1
#define LEFT -1
#define UP 2
#define DOWN -2

/*test if a pointer was allocated properly*/
void mallocTest(void *p);

/*alloc a matrix r x c*/
unsigned int **allocateMatrix( unsigned int row, unsigned int column);

game_t *instantiateGame();

void freeMatrix(unsigned int **m);

unsigned int readInput();

unsigned int currentColor(game_t *game);

int checkNeighbor(game_t *g, stack_t *s, int direction, unsigned int color);

void flood(game_t *g, stack_t *s, unsigned int color);

void floodIt(game_t *game, unsigned int i, stack_t *s);

#endif