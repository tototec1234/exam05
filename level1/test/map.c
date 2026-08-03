#include "a.h"

char** map_alloc(int h, int w, char f)
{
	char** map=(char**)calloc(h + 2, sizeof(char *));
	if (!map)
		return NULL;
	for (int y = 0; y < h + 2; y++)
	{
		map[y] = (char*)calloc(w + 3, sizeof(char));
		if (!map[y])
			map_free(map, y);
		for (int x = 0; x < w + 3; x++)
			map[y][x] = f;
	}
	return map;
}

char** map_free(char **map, int h)
{
	if (!map)
		return NULL;
	for (int y = 0; y <= h; y++)
		free(map[y]);
	free(map);
	return NULL;
}

char** map_print(char **map, int h, int w)
{
	if (!map)
		return NULL;
	for (int y = 0; y <= h ; y++)
		printf("%.*s\n", w + 1, map[y]);
	return map;
}