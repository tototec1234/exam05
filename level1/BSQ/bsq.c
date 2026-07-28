#include "bsq.h"

static int	is_printable(char c)
{
	return (c >= 32 && c <= 126);
}

static void	fill_border(char **map, int w, int h, char obst)
{
	for (int x = 0; x < w + 2; x++)
	{
		map[0][x] = obst;
		map[h + 1][x] = obst;
	}
	for (int y = 1; y <= h; y++)
	{
		map[y][0] = obst;
		map[y][w + 1] = obst;
	}
}


int	parse(FILE *fp, char ***map, int *w, int *h,
		char *empty, char *obst, char *full)
{
	char	*line = NULL;
	size_t	cap = 0;
	int		len;

	if (fscanf(fp, "%d %c %c %c", h, empty, obst, full) != 4)
		return (-1);
	if (*h <= 0 || !is_printable(*empty) || !is_printable(*obst)	|| !is_printable(*full)
		|| *empty == *obst || *empty == *full || *obst == *full)
		return (-1);
	if (getline(&line, &cap, fp) == -1)
		return (free(line), -1);

	*map = NULL;
	*w = 0;
	for (int y = 1; y <= *h ; y++)
	{
		len = (int)getline(&line, &cap, fp) - 1;
		if (len <= 0 || line[len] != '\n')
			return (free(line), free_board(*map, *h + 2 ), -1);
		if (y == 1)
		{
			*w = len;
			*map = alloc_board(*w, *h);
			if (!*map)
				return (free(line), -1);
			fill_border(*map, *w, *h, *obst);
		}
		else if (len != *w)
			return (free(line), free_board(*map, *h + 2) , -1);
		
		for (int x = 0; x < *w ; x++)
		{
			if (line[x] != *empty && line[x] != *obst)
				return (free(line), free_board(*map, *h + 2), -1);
			(*map)[y][x + 1] = line[x];
		}
	}
	free(line);
	return (0);
}


void	solve(char **map, int w, int h, char obst, char full)
{
	int	dp[h + 2][w + 2];
	int	best = 0, 	bi = 1,	bj = 1,	min;

	for (int x = 0; x < w + 2; x++)
		dp[0][x] = 0;
	
	for (int y = 1; y <= h; y++)
	{
		dp[y][0] = 0;
		for (int x = 1; x <= w; x++)
		{
			if (map[y][x] == obst)
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
			map[y][x] = full;
}


int	run(FILE *fp)
{
	char	**map;
	int		w, h;
	char	empty, 	obst, full;

	if (parse(fp, &map, &w, &h, &empty, &obst, &full) == -1)
		return (-1);
	solve(map, w, h, obst, full);
	for (int y = 1; y <= h; y++)
		fprintf(stdout, "%.*s\n", w, &map[y][1]);
	free_board(map, h + 2);
	return (0);
}

int	main(int argc, char **argv)
{
	FILE	*fp;

	if (argc == 1)
		if (run(stdin) == -1)
			return (fprintf(stderr, "map error\n") , 0);
	for (int i = 1; i < argc ; i++)
	{
		fp = fopen(argv[i], "r");
		if (!fp || run(fp) == -1)
			fprintf(stderr, "map error\n");
		if (fp)
			fclose(fp);
		if (i < argc - 1)
			fprintf(stdout, "\n");
	}
	return (0);
}

/*
cc -Wall -Wextra -Werror -o bsq board.c bsq.c
*/
