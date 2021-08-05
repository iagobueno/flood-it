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

int minimum(int a, int b){
    if(a > b)
        return b;
    return a;
}

int corner(int a, int b, int c){

    int min = a;

    if(min > b)
        min = b;

    if(min > c)
        min = c;

    return min;
}

int distance(game_t *game, int **board, stack_t *stack, int new){
    if(currentColor(board, 0, 0) == new)
        return 32000;

    // create a copy of our board
    int **aux = createMatrix(game);
    copyMatrix(aux, board, game->row, game->column);
    // printMatrix(aux, game->row, game->column);
    
    //floot it with the color
    floodIt(game, aux, new, stack, 0, 0);
    // printMatrix(aux, game->row, game->column);
    floodIt(game, aux, 0, stack, 0, 0);
    // printMatrix(aux, game->row, game->column);

    unsigned int count = 0;
    int i = 0, j, up, left, min = 0;

    //mesmo for do for abaixo, mas rodas apenas para a linha 1 pra reduzir a quantidade de ifs
    for(j = 0; j < game->column; j++){
        if(aux[i][j] > 0){

            if(j > 0){
                left = abs(aux[i][j-1]) + 1;
            }

            floodIt(game, aux, left*(-1), stack, i, j);
            count++;
            // printMatrix(aux, game->row, game->column);
        }
    }

    for(i = 1; i < game->row; i++){
        for(j = 0; j < game->column; j++){
            if(aux[i][j] > 0){

                up = abs(aux[i-1][j]);

                if(j > 0){
                    left = abs(aux[i][j-1]);
                }
                else
                    left = up;


                min = minimum(up, left) + 1;
                
                floodIt(game, aux, min*(-1), stack, i, j);
                count++;
                // printMatrix(aux, game->row, game->column);
            }
        }
    }

    // int co = corner(aux[0][game->column-1], aux[game->row-1][0], aux[game->row-1][game->column-1]);
    int co = aux[game->row-1][game->column-1];

    // printMatrix(aux, game->row, game->column);
    // printf("Clusters: %d\n", count);
    freeMatrix(aux);
    return co*(-1);
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

    int i, min, c = 1, heu;
    min = countCluster(game, board, stack, 1) + distance(game, board, stack, i);
    
    printf("c: %d ", min);

    for(i = 2; i <= game->color; i++){
        heu = countCluster(game, board, stack, i) + distance(game, board, stack, i);
        printf("%d ", heu);

        if (min > heu){
            min = heu;
            c = i;
        }
    }
    printf("heu:%d \n", c);

    //stores the choosed color
    if(game->round < SIZE)
        result[game->round] = c;

    return c;
}