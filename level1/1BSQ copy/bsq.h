#ifndef BSQ_H
#define BSQ_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char **alloc_board(int h, int w, char obstacle);
char **free_board(char** board, int h );
int print_board(char** board, int h ,int w);
int run(FILE* fp);

#endif
