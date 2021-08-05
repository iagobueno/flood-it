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

    // srand(time(NULL));

    //read board, numbers of rows, columns and colors;
    game_t *game = createGame();
    int **board = createMatrix(game);
    readBoard(game, board);

    //result array
    unsigned int *result = malloc(sizeof(unsigned int) * SIZE);

    //set stack
    stack_t *stack = createStack(game->row, game->column);

    //run the game
    while(game->status == RUNNING){
        printScreen(game, board);
        floodIt(game, board, chooseMove(game, board, stack, result), stack, 0, 0);
        gameStatus(game, board);
        sleep(1);
    }
    printScreen(game, board);
    printArray(result, game->round);

    //free and nulify
    freeStack(stack);
    freeMatrix(board);
    free(game);
    free(result);
    return 0;
}