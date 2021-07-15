#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <time.h>
#include<unistd.h>

void mallocTest(void *p){
    if(!p){
        fprintf(stderr, "Malloc failure");
        exit(1);
    }
}

unsigned int **allocateMatrix( unsigned int row, unsigned int column){
    unsigned int **new = (unsigned int **) malloc(sizeof(unsigned int*) * row);
    mallocTest(new);

    new[0] = (unsigned int*) malloc(row * column * sizeof(unsigned int));
    mallocTest(new[0]);

    int i;
    for(i = 1; i < row; i++)
        new[i] = new[0] + i * column;

    return new;
}

game_t *instantiateGame(){
    game_t *g = (game_t*) malloc(sizeof(game_t));
    unsigned int row, column, color;

    /*read and set the numbers of columns, rows and colors*/
    fscanf(stdin, "%u %u %u", &row, &column, &color);
    g->column = column;
    g->row = row;
    g->color = color;
    g->status = RUNNING;

    /*read and set the board*/
    g->board = allocateMatrix(row, column);
    int i ,j;
    for(i = 0; i < g->row; i++)
        for (j = 0; j < g->column; j++)
            g->board[i][j] = (rand () % color) + 1;
            // fscanf(stdin, "%u", &(g->board[i][j]));

    
    return g;
}

void freeMatrix(unsigned int **m){
    free(m[0]);
    free(m);
}

unsigned int currentColor(game_t *game){
    return game->board[0][0];
}

void flood(game_t *g, stack_t *s, unsigned int color){
    g->board[(s->r)[s->top]][(s->c)[s->top]] = color;
}

int checkNeighbor(game_t *g, stack_t *s, int direction, unsigned int color){

    if(direction == RIGHT){
        if(( (s->c)[s->top] + 1 < g->column) && ( g->board[ (s->r)[s->top] ][ (s->c)[s->top] + 1 ] == color ))
            return 1;
        return 0;
    }
    else if(direction == LEFT){
        if(( (s->c)[s->top] > 0) && (g->board[ (s->r)[s->top] ][ (s->c)[s->top] - 1] == color ))
            return 1;
        return 0;
    }
    else if(direction == DOWN){
        if(( (s->r)[s->top] + 1 < g->row) && ( g->board[ (s->r)[s->top] + 1 ][ (s->c)[s->top] ] == color ))
            return 1;
        return 0;
    }
    else{
        if(( (s->r)[s->top] > 0) && ( g->board[ (s->r)[s->top] - 1 ][ (s->c)[s->top] ] == color ))
            return 1;
        return 0;
    }
}

void floodIt(game_t *g, unsigned int new, stack_t *s){

    unsigned int curr = currentColor(g);

    if(curr == new)
        return;

    stackUp(s, 0, 0);
    flood(g, s, new);

    for(;s->top >= 0;){
        if( checkNeighbor(g, s, RIGHT, curr) ){
            stackUp(s, s->r[s->top], s->c[s->top] + 1);
            flood(g, s, new);
        }
        else if( checkNeighbor(g, s, LEFT, curr) ){
            stackUp(s, s->r[s->top], s->c[s->top] - 1);
            flood(g, s, new);
        }
        else if( checkNeighbor(g, s, DOWN, curr) ){
            stackUp(s, s->r[s->top] + 1, s->c[s->top]);
            flood(g, s, new);
        }
        else if( checkNeighbor(g, s, UP, curr) ){
            stackUp(s, s->r[s->top] - 1, s->c[s->top]);
            flood(g, s, new);
        }
        else
            unstack(s);
    }

    // int j;
    // for(j = 0; j < k && s->size >0 ;){

    //     if( (s->a)[j] + 1 < g->row && g->board[(s->a)[j] + 1 ][(s->b)[j]] == curr){
    //         stackUp(s, (s->a)[j] + 1, (s->b)[j], j);
    //         j++;
    //         flood(g, s->a[j], s->b[j], new);
    //     }

    //     else{
    //         s->size--;
    //         j--;
    //     }
    // }
}

unsigned int readInput(){

    unsigned int i;
    fscanf(stdin, "%u", &i);

    return i;
}