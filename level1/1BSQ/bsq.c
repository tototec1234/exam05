#include "bsq.h"

static int is_print(char c){	return (32 <= c && c <= 126); }

static int parse(FILE *fp, char ***map, int *h, int *w, char *e, char *o, char *f)
{
	char *line = NULL;
	size_t cap = 0;
	int len;

	*map = NULL;
	*w = 0;
	if (fscanf(fp, "%d %c %c %c", h, e, o, f) != 4)
		return (-1);
	if (*h <= 0 || !is_print(*e) || !is_print(*o) || !is_print(*f)
		|| *e == *o || *e == *f || *o == *f)
		return (-1);
	if (getline(&line, &cap, fp) == -1)
		return (free(line), -1);
	for (int y = 1; y <= *h; y++)
	{
		len = (int)getline(&line, &cap, fp) - 1;
		if (len <= 0 || line[len] != '\n')
			return (free(line), *map = free_board(*map, *h), -1);
		if (y == 1)
		{
			*w = len;
			*map = alloc_board(*h, *w, *o);
			if (!*map)
				return (free(line), -1);
		}
		else if (len != *w)
			return (free(line), *map = free_board(*map, *h), -1);
		for (int x = 0; x < *w; x++)
		{
			if (line[x] != *e && line[x] != *o)
				return (free(line), *map = free_board(*map, *h), -1);
			(*map)[y][x + 1] = line[x];
		}
	}
	return (free(line), 0);
}

static int solv(char **map, int h, int w, char o, char f)
{
	int (*dp)[w + 2] = calloc(h + 2, sizeof(*dp));
	int best = 0, by = 1, bx = 1, min;

	if (!dp)
		return (-1);
	for (int y = 1; y <= h; y++)
	{
		for (int x = 1; x <= w; x++)
		{
			if (map[y][x] == o)
				continue;
			min = dp[y - 1][x];
			if (dp[y - 1][x - 1] < min)
				min = dp[y - 1][x - 1];
			if (dp[y][x - 1] < min)
				min = dp[y][x - 1];
			dp[y][x] = min + 1;
			if (dp[y][x] > best)
			{
				best = dp[y][x];
				by = y - best + 1;
				bx = x - best + 1;
			}
		}
	}
	for (int y = by; y < by + best; y++)
		for (int x = bx; x < bx + best; x++)
			map[y][x] = f;
	return (free(dp), 0);
}

int run(FILE *fp)
{
	char **map;
	int h, w;
	char empty, obstacle, full;

	if (parse(fp, &map, &h, &w, &empty, &obstacle, &full) == -1)
		return (-1);
	if (solv(map, h, w, obstacle, full) == -1)
		return (free_board(map, h), -1);
	for (int y = 1; y <= h; y++)
		fprintf(stdout, "%.*s\n", w, map[y] + 1);
	free_board(map, h);
	return (0);
}
