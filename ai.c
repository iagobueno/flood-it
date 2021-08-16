#include "ai.h"
#include "game.h"
#include "print.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//copy the source matrix to the destiny matrix
void copyMatrix(int **dest, int **src, unsigned int r, unsigned c){
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < c; j++)
            dest[i][j] = src[i][j];
    }

}

//checks the minimun between a and b
int minimum(int a, int b){
    if(a > b)
        return b;
    return a;
}

int diagonal(game_t *game, int **board, stack_t *stack, int new){
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


    //mesmo for do for abaixo, mas rodas apenas para a linha 1 pra reduzir a quantidade de ifs
    int up, left, min = 0;
    int i, j;
    i = 0;
    for(j = 0; j < game->column; j++){
        if(aux[i][j] > 0){

            if(j > 0){
                left = abs(aux[i][j-1]) + 1;
            }

            // floodIt(game, aux, left*(-1), stack, i, j);
            aux[i][j] = left*(-1);
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
                
                aux[i][j] = min*(-1);
                // floodIt(game, aux, min*(-1), stack, i, j);
                // printMatrix(aux, game->row, game->column);
            }
        }
    }

    // int co = corner(aux[0][game->column-1], aux[game->row-1][0], aux[game->row-1][game->column-1]);
    int co = aux[game->row-1][game->column-1];

    // printMatrix(aux, game->row, game->column);
    freeMatrix(aux);
    return co*(-1);
}

int countCluster(game_t *game, int **board, stack_t *stack, int new){

    if(currentColor(board, 0, 0) == new)
        return 32000;

    // create a temporary matrix
    int **aux = createMatrix(game);
    copyMatrix(aux, board, game->row, game->column);

    // flood it with zeros
    floodIt(game, aux, new, stack, 0, 0);

    unsigned int count = 0;
    unsigned int i, j;
    for(i = 0; i < game->row; i++){

        for(j = 0; j < game->column; j++){

            // flood a cluster with zero and count one
            // and don't count the zeros clusters
            if(aux[i][j] >= 0){
                floodIt(game, aux, aux[i][j]*(-1), stack, i, j);
                count++;
            }
        }
    }

    freeMatrix(aux);
    return count;
}

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
}

int partition (int *arr, int *arr2, int low, int high) 
{ 
    int pivot = arr[high]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++; // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
            swap(&arr2[i], &arr2[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    swap(&arr2[i + 1], &arr2[high]); 
    return (i + 1); 
}

void quickSort(int *arr, int *arr2, int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now at right place */
        int pi = partition(arr, arr2, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, arr2, low, pi - 1); 
        quickSort(arr, arr2, pi + 1, high); 
    } 
}

int *countColors(game_t *game, int **board){

    unsigned int *color_count = calloc((game->color + 1), sizeof(unsigned int));

    unsigned int i, j;
    for(i = 0; i < game->row; i++){
        for(j = 0; j < game->column; j++)
            color_count[board[i][j]]++;
    }

    unsigned int *color_array = malloc( (game->color + 1) * sizeof(unsigned int));
    for(i = 0; i < game->color+1; i++){
        color_array[i] = i;
    }

    quickSort(color_count, color_array, 1, (game->color));
    printf("COLOR COUNT: ");
    printArray(color_count, game->color + 1 );
    printf("COLOR ARRAY: ");
    printArray(color_array, game->color + 1 );

    free(color_count);
    return color_array;
}

int chooseMove(game_t *game, int **board, stack_t *stack, int *result, int *color_count){

    int i, j, j_init = 1, min_c = 32000, min_f = 32000, c_c = 1, c_f = 1, heu;
    if(game->color > 10)
        j_init = game->color - 10 + 1;

    // run the current 
    // for(i = 1; i <= game->color; i++){

    // }


    for(i = 1; i <= game->color; i++){

        heu = countCluster(game, board, stack, i) + diagonal(game, board, stack, i);

        if (min_c > heu){
            min_c = heu;
            c_c = i;
        }
        // create an aux matrix
        int **aux = createMatrix(game);
        copyMatrix(aux, board, game->row, game->column);

        // flood it with the color i
        floodIt(game, aux, i, stack, 0, 0);

        // printf("j_init: %d\n", j_init);
        // printf("\npintando de %d, temos as heuristicas:\n\n", i);
        if(game->round > 200)
            j = game->color + 1;
        for(j = j_init; j <= game->color; j++){


            heu = countCluster(game, aux, stack, color_count[j]) + diagonal(game, aux, stack, color_count[j]);

            // printf("color_count[j]: %d - h: %d || ", color_count[j], heu);

            if (min_f > heu){
                min_f = heu;
                c_f = i;
                // printf("COR MUDOU PARA: %d || ", c_f);
            }

        }

        freeMatrix(aux);
    }

    int c;
    if(min_f < min_c)
        c = c_f;
    else
        c = c_c;

    // printf("COR FINAL:%d \n", c);

    //stores the choosed color in the result array
    if(game->round < SIZE)
        result[game->round] = c;

    return c;
}