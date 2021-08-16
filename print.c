#include "print.h"
#include "game.h"
#include <stdio.h>

// display colors when printing the screen
void color(int c){
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
        case 8 :
            printf(GRAY);
            break;
        case 9 :
            printf(HRED);
            break;
        case 10 :
            printf(HYEL);
            break;
        default :
            printf(BLACK);
            break;
    }

    printf("%d ", c);
    // printf("▀ ");
}

// print a Matrix on the screen
void printMatrix(int **m, unsigned int r, unsigned int c){
    int i, j;
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++)
            printf("%d ", m[i][j]);
            // color(m[i][j]);
        printf("\n");
    }
    printf("\n");
    printf(BLACK);

}

// print a Array on the screen
void printArray(int *a, unsigned int size){
    int i;

    printf("resultado: ");

    for(i = 0; i<size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// print game board and rounds
void printScreen(game_t *game, int **board){
    printMatrix(board, game->row, game->column);
    printf("rounds: %u\n", game->round);
}