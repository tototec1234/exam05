#include "bsq.h"

char	**alloc_board(int w, int h)
{
	char	**map = malloc(sizeof(char *) * (h + 2));

	if (!map)
		return (NULL);
	for (int y = 0; y < h + 2; y++)
	{
		map[y] = malloc(w + 3);
		if (!map[y])
			return (free_board(map, y), NULL);
		for (int x = 0; x < w + 2; x++)
			map[y][x] = ' ';
		map[y][w + 2] = '\0';
	}
	return (map);
}

void	free_board(char **map, int rows)
{
	if (!map)
		return ;
	for (int y = 0; y < rows; y++)
		free(map[y]);
	free(map);
}
