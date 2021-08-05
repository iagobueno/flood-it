/*library that is responsible for printing every element of the game*/
#ifndef PRINT_H
#define PRINT_H
#include "game.h"

#define TIME 30000
#define RED "\033[1;31m" 
#define YELLOW "\033[1;33m" 
#define BLUE "\033[1;34m" 
#define WHITE "\033[1;37m" 
#define GREEN "\033[1;32m" 
#define PURPLE "\033[1;35m" 
#define CYAN "\033[1;36m" 
#define BLACK "\033[1;30m"

void printMatrix(int **m, unsigned int r, unsigned int c);

void printArray(int *a, unsigned int size);

void color(int c);

void printScreen(game_t *game);

#endif