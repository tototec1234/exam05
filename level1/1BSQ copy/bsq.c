#include "bsq.h"

int is_print(char c)
{
	if ( c < 32 || 126 < c)
		return 0;
	return 1;
}

int parse(FILE* fp, char ***map, int *w, int *h, char *e, char *o, char *f )
{
	char *line = NULL;
	size_t cap = 0;
	int len;

	if (fscanf(fp,"%d %c %c %c", h, e, o, f) != 4 )
		return(-1);
	if (*h <= 0 || !is_print(*e) || !is_print(*o) || !is_print(*f) || *e == *o || *e == *f  || *o == *f )
		return(-1);
	

	if (getline(&line, &cap, fp) == -1)
		return (free(line), -1);

	*map = NULL;
	*w = 0;
	
	for (int y = 1; y <= *h ; y++)
	{
		len = (int)getline(&line, &cap, fp) - 1;
		if (len <= 0 || line[len] != '\n')
			return (free(line), free_board(*map, *h), -1);
		if (y == 1)
		{
			*w = len;
			*map = alloc_board(*h, *w, *o);
			if (!*map)
				return (free(line), -1);
		}
		else if (len != *w)
			return (free(line), free_board(*map, *h), -1);
		
		for (int x = 0; x < *w ; x++)
		{
			if (line[x] != *e && line[x] != *o )
				return (free(line), free_board(*map,  *h), -1);
			(*map)[y][x + 1] = line[x];
		}
	}
	free(line);

	return 0;
}


int solv(char **map, int w, int h, char o, char f)
{
	int dp[h + 2][w + 2];
	int best = 0, bi = 1, bj = 1,min;

	for (int x = 0; x < w + 2; x++)
		dp[0][x] = 0;

	for (int y = 1; y <= h; y++)
	{
		dp[y][0] = 0;
		for (int x = 1; x < w + 1; x++)
		{
			if (map[y][x] == o)
				dp[y][x] = 0;
			else
			 {
				min = dp[y - 1][x];
				if (dp[y - 1][x - 1] < min)
					min = dp[y - 1][x - 1];
				if (dp[y][x - 1] < min)
					min = dp[y][x - 1];
				dp[y][x] = min + 1;
			 }
			 if (dp[y][x] > best)
			 {
				best = dp[y][x];
				bi = y - best + 1;
				bj = x - best + 1;
			 }
		}
	}
	for (int y = bi; y < bi + best; y++)
		for (int x = bj; x < bj + best; x++)
			map[y][x] = f;
	return 0;
}

int run(FILE* fp)
{
	char **map;
	int h, w;
	char empty, obstacle, full;

	if (parse(fp, &map, &w, &h, &empty, &obstacle, &full) == -1)
		return -1;
	solv(map, w, h, obstacle, full);
	for (int i = 1; i < h + 1; i++)
		fprintf(stdout, "%.*s\n", w, map[i] + 1);
	free_board(map, h);
	return 0;
}
