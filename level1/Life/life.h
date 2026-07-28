#ifndef LIFE_H
# define LIFE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	**alloc_board(int w, int h);
void	free_board(char **map, int rows);

#endif
