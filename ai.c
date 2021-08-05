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

int countCluster(game_t *game, int **board, stack_t *stack, int new){

    if(currentColor(board, 0, 0) == new)
        return 32000;

    int **aux = createMatrix(game);
    copyMatrix(aux, board, game->row, game->column);

    floodIt(game, aux, new, stack, 0, 0);

    unsigned int count = 0;
    int i, j;
    for(i = 0; i < game->row; i++){
        for(j = 0; j < game->column; j++){
            if(aux[i][j] >= 0){
                floodIt(game, aux, aux[i][j]*(-1), stack, i, j);
                count++;
            }
        }
    }

    freeMatrix(aux);
    return count;
}

int chooseMove(game_t *game, int **board, stack_t *stack, int *result){

    // c = rand () % colors + 1;

    // unsigned int *heu = malloc(sizeof(unsigned int) * game->color);

    int i, min, c = 1, cluster;
    min = countCluster(game, board, stack, 1);
    
    printf("c: %d ", min);

    for(i = 2; i <= game->color; i++){
        cluster = countCluster(game, board, stack, i);
        printf("%d ", cluster);

        if (min > cluster){
            min = cluster;
            c = i;
        }
    }
    printf("heu:%d \n", c);

    //stores the choosed color
    if(game->round < SIZE)
        result[game->round] = c;

    return c;
}