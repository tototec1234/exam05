#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>

char **alloc_board(int h, int w, char fill);
char **free_board(char **board, int h);
int print_board(char **board, int h, int w);
int run(FILE *fp);

#endif
