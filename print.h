/*library that is responsible for printing every element of the game*/
#ifndef PRINT_H
#define PRINT_H
#include "game.h"

#define TIME 30000
#define GRAY "\033[1;30m"
#define RED "\033[1;31m" 
#define GREEN "\033[1;32m" 
#define YELLOW "\033[1;33m" 
#define BLUE "\033[1;34m" 
#define PURPLE "\033[1;35m" 
#define CYAN "\033[1;36m" 
#define WHITE "\033[1;37m" 
#define BLACK "\e[0m"
#define HRED "\e[0;91m"
#define HYEL "\e[0;93m"

void printMatrix(int **m, unsigned int r, unsigned int c);

void printArray(int *a, unsigned int size);

void color(int c);

void printScreen(game_t *game, int **board);

#endif