/*library that is responsible for basic game structures*/
#ifndef GAME_H
#define GAME_H
#define SIZE 300
#include "stack.h"
#define INT_MAX 2147483647

typedef struct{
    unsigned int row, column, color, status, round;
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
int **createMatrix( game_t *g);

game_t *createGame();

void readBoard(game_t *g, int **b);

unsigned int currentColor(int **m, unsigned int init_x, unsigned int init_y);

int checkNeighbor(game_t *g, int **b, stack_t *s, int direction, int color);

void flood(int **m, stack_t *s, int color);

void floodIt(game_t *g, int **m, int new, stack_t *s, unsigned int init_x, unsigned int init_y);

int isOver(game_t *game, int **board);

void gameStatus(game_t *game, int **board);

void freeMatrix(int **m);

#endif