#ifndef LIFE_H
# define LIFE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char	**alloc_board(int w, int h);
void	free_board(char **map, int h);

#endif
