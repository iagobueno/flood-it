#ifndef AI
#define AI
#include "game.h"

int countCluster(game_t *game, int **board, stack_t *stack, int color);

int distance(game_t *game, int **board, stack_t *stack, int new);

int chooseMove(game_t *game, int **board, stack_t *stack, int *result);

int diagonal(game_t *game, int **board, stack_t *stack, int new, int *zero);

#endif