#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "game.h"
#include "print.h"

int main(){

    //read board, numbers of rows, columns and colors
    game_t *game;
    game = createGame();

    //set stack
    stack_t *stack = createStack(game->row, game->column);


    //run the game
    while(game->status == RUNNING){
        printScreen(game);
        floodIt(game, readInput(), stack);
        gameStatus(game);
    }
    printScreen(game);

    //free and nulify
    freeStack(stack);
    freeGame(game);
    stack = NULL;
    game = NULL;
    return 0;
}