#include "ai.h"
#include "game.h"
#include "print.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void copyMatrix(int **dest, int **src, unsigned int r, unsigned c){
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < c; j++)
            dest[i][j] = src[i][j];
    }

}

unsigned int countCluster(game_t *game){

    unsigned int row, column;
    row = game->row;
    column = game->column;

    game_t *aux = createGame();
    copyMatrix(aux->board, game->board, row, column);
    aux->column = column;
    aux->row = row;
    aux->color = game->color;

    printMatrix(aux->board, row, column);

    // int i, j;
    // for(i = 0; i < row; i++){
    //     for(j = 0; j < column; j++){
    //         if(aux->board[i][j] >= 0);

    //     }
    // }

    freeGame(aux);
    return 1;
}

int chooseMove(int *result, int colors, int i){

    //chooses a color
    int c;
    // c = rand () % colors + 1;
    scanf("%d", &c);

    //stores the choosed color
    if(i < SIZE)
        result[i] = c;

    return c; 
}