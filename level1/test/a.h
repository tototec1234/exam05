#ifndef A_H
#define A_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char** map_alloc(int h, int w, char f);
char** map_free(char **map, int h);
char** map_print(char **map, int h, int w);


#endif
