#include "print.h"
#include "game.h"
#include <stdio.h>

void color(unsigned int c){
    switch (c){
        case 1 :
            printf(RED);
            break;
        case 2 :
            printf(YELLOW);
            break;
        case 3 :
            printf(BLUE);
            break;
        case 4 :
            printf(WHITE);
            break;
        case 5 :
            printf(GREEN);
            break;
        case 6 :
            printf(PURPLE);
            break;
        case 7 :
            printf(CYAN);
            break;
        default :
            printf(BLACK);
            break;
    }

    printf("%u ", c);
}

void printMatrix(unsigned int **m, unsigned int r, unsigned int c){
    int i, j;
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++)
            color(m[i][j]);
        printf("\n");
    }
    printf(BLACK);

}

void printScreen(game_t *game){
    printMatrix(game->board, game->row, game->column);
}