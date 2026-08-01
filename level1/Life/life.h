#ifndef LIFE_H
# define LIFE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	**alloc_board(int h, int w, char fill);
char	**free_board(char **board, int h);
int		print_board(char **board, int h, int w);

#endif
