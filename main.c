#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "game.h"
#include "print.h"
#include "ai.h"
#include <unistd.h>
#include <stdlib.h>
#include<time.h>

int main(){

    //read board, numbers of rows, columns and colors
    game_t *game;
    game = createGame();

    unsigned int *result = malloc(sizeof(unsigned int) * SIZE);

    srand(time(NULL));

    //set stack
    stack_t *stack = createStack(game->row, game->column);
    // countCluster(game);

    //run the game
    while(game->status == RUNNING){
        printScreen(game);
        floodIt(game, chooseMove(result, game->color, game->round), stack, 0, 0);
        gameStatus(game);
        // sleep(1);
    }
    printScreen(game);
    printArray(result, game->round);

    //free and nulify
    freeStack(stack);
    freeGame(game);
    free(result);
    return 0;
}