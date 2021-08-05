/*library that is responsible for basic game structures*/
#ifndef GAME_H
#define GAME_H
#define SIZE 300
#include "stack.h"

typedef struct{
    unsigned int row, column, color, status, round;
    int **board;
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
int **createMatrix( unsigned int row, unsigned int column);

game_t *createGame();

unsigned int currentColor(game_t *game, unsigned int init_x, unsigned int init_y);

int checkNeighbor(game_t *g, stack_t *s, int direction, int color);

void flood(game_t *g, stack_t *s, int color);

void floodIt(game_t *g, int new, stack_t *s, unsigned int init_x, unsigned int init_y);

int isOver(game_t *game);

void gameStatus(game_t *game);

void freeMatrix(int **m);

void freeGame(game_t *game);

#endif