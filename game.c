#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <time.h>
#include<unistd.h>

//test if malloc is ok
void mallocTest(void *p){
    if(!p){
        fprintf(stderr, "Malloc failure");
        exit(1);
    }
}

// allocate a matrix in method contiguous line pointer vector
int **createMatrix( unsigned int row, unsigned int column){
    int **new = (int **) malloc(sizeof(int*) * row);
    mallocTest(new);

    new[0] = (int*) malloc(row * column * sizeof(int));
    mallocTest(new[0]);

    int i;
    for(i = 1; i < row; i++)
        new[i] = new[0] + i * column;

    return new;
}

game_t *createGame(){
    game_t *g = (game_t*) malloc(sizeof(game_t));
    
    /*read and set the numbers of columns, rows and colors*/
    unsigned int row, column, color;
    fscanf(stdin, "%u %u %u", &row, &column, &color);
    g->column = column;
    g->row = row;
    g->color = color;

    //set game status and rounds
    g->status = RUNNING;
    g->round = 0;

    /*read and set the board*/
    g->board = createMatrix(row, column);
    int i ,j;
    for(i = 0; i < g->row; i++)
        for (j = 0; j < g->column; j++)
            g->board[i][j] = (rand () % color) + 1;
            // fscanf(stdin, "%u", &(g->board[i][j]));
            
    return g;
}

unsigned int currentColor(game_t *game, unsigned int init_x, unsigned int init_y){
    return game->board[init_x][init_y];
}

void flood(game_t *g, stack_t *s, int color){
    //flood a single square on the board
    g->board[(s->r)[s->top]][(s->c)[s->top]] = color;
}

int checkNeighbor(game_t *g, stack_t *s, int direction, int color){

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

void floodIt(game_t *g, int new, stack_t *s, unsigned int init_x, unsigned int init_y){

    int curr = currentColor(g, init_x, init_y);

    if(curr == new)
        return;

    stackUp(s, init_x, init_y);
    flood(g, s, new);

    //check all neighbors and flood them
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
}

int isOver(game_t *game){

    int curr = currentColor(game, 0, 0);

    int i, j;
    for(i = 0; i < game->row; i++){
        for(j = 0; j < game-> column; j++){
            if(game->board[i][j] != curr)
                return 0;
        }
    }
    return 1;
}

void gameStatus(game_t *game){

    //count a round
    game->round++;

    //check if game is over
    if(isOver(game))
        game->status = SHUTDOWN;
}

void freeMatrix(int **m){
    free(m[0]);
    free(m);
}

void freeGame(game_t *game){
    freeMatrix(game->board);
    free(game);
}