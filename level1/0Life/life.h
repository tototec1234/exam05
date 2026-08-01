#ifndef LIFE_H
#define LIFE_H

#include <unistd.h>
#include <stab.h>
#include <stdlib.h>

char **alloc_board(int w, int h);
void free_board(char **map, int rows);



#endif