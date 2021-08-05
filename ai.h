#ifndef AI
#define AI
#include "game.h"

int countCluster(game_t *game, int **board, stack_t *stack, int color);

int chooseMove(game_t *game, int **board, stack_t *stack, int *result);

#endif