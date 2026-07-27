#include "bsq.h"

char	**alloc_board(int w, int h)
{
	char	**map;
	int		y;

	map = malloc(sizeof(char *) * h);
	if (!map)
		return (NULL);
	y = 0;
	while (y < h)
	{
		map[y] = malloc(w + 1);
		if (!map[y])
		{
			free_board(map, y);
			return (NULL);
		}
		// for (int x = 0; x < w; x++){map[y][x] = ' ';}
		map[y][w] = '\0';
		y++;
	}
	return (map);
}

void	free_board(char **map, int h)
{
	int	y;

	if (!map)
		return ;
	y = 0;
	while (y < h)
	{
		free(map[y]);
		y++;
	}
	free(map);
}

static int	is_printable(char c)
{
	return (c >= 32 && c <= 126);
}

static int	copy_line(char *dst, char *src, int w)
{
	int	x;

	x = 0;
	while (x < w)
	{
		dst[x] = src[x];
		x++;
	}
	dst[w] = '\0';
	return (0);
}

int	parse(FILE *fp, char ***map, int *w, int *h,
		char *empty, char *obst, char *full)
{
	char	*line;
	size_t	cap;
	ssize_t	len;
	int		y;
	int		x;

	line = NULL;
	cap = 0;
	if (fscanf(fp, "%d %c %c %c", h, empty, obst, full) != 4)
		return (-1);
	if (*h <= 0 || !is_printable(*empty) || !is_printable(*obst)
		|| !is_printable(*full))
		return (-1);
	if (*empty == *obst || *empty == *full || *obst == *full)
		return (-1);
	if (getline(&line, &cap, fp) == -1)
	{
		free(line);
		return (-1);
	}
	*map = NULL;
	*w = 0;
	y = 0;
	while (y < *h)
	{
		len = getline(&line, &cap, fp);
		if (len <= 0 || line[len - 1] != '\n')
		{
			free(line);
			free_board(*map, y);
			return (-1);
		}
		len--;
		if (len <= 0)
		{
			free(line);
			free_board(*map, y);
			return (-1);
		}
		if (y == 0)
		{
			*w = (int)len;
			*map = alloc_board(*w, *h);
			if (!*map)
			{
				free(line);
				return (-1);
			}
		}
		else if ((int)len != *w)
		{
			free(line);
			free_board(*map, *h);
			return (-1);
		}
		x = 0;
		while (x < *w)
		{
			if (line[x] != *empty && line[x] != *obst)
			{
				free(line);
				free_board(*map, *h);
				return (-1);
			}
			x++;
		}
		copy_line((*map)[y], line, *w);
		y++;
	}
	free(line);
	return (0);
}

void	solve(char **map, int w, int h, char empty, char obst, char full)
{
	int	dp[h][w];
	int	best;
	int	bi;
	int	bj;
	int	y;
	int	x;
	int	m;

	(void)empty;
	best = 0;
	bi = 0;
	bj = 0;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (map[y][x] == obst)
				dp[y][x] = 0;
			else if (y == 0 || x == 0)
				dp[y][x] = 1;
			else
			{
				m = dp[y - 1][x];
				if (dp[y - 1][x - 1] < m)
					m = dp[y - 1][x - 1];
				if (dp[y][x - 1] < m)
					m = dp[y][x - 1];
				dp[y][x] = m + 1;
			}
			if (dp[y][x] > best)
			{
				best = dp[y][x];
				bi = y - best + 1;
				bj = x - best + 1;
			}
			x++;
		}
		y++;
	}
	y = bi;
	while (y < bi + best)
	{
		x = bj;
		while (x < bj + best)
		{
			map[y][x] = full;
			x++;
		}
		y++;
	}
}

void	print_board(char **map, int h)
{
	int	y;

	y = 0;
	while (y < h)
	{
		fputs(map[y], stdout);
		fputc('\n', stdout);
		y++;
	}
}

int	run(FILE *fp)
{
	char	**map;
	int		w;
	int		h;
	char	empty;
	char	obst;
	char	full;

	if (parse(fp, &map, &w, &h, &empty, &obst, &full) == -1)
		return (-1);
	solve(map, w, h, empty, obst, full);
	print_board(map, h);
	free_board(map, h);
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	FILE	*fp;

	if (argc == 1)
	{
		if (run(stdin) == -1)
			fprintf(stderr, "map error\n");
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			fp = fopen(argv[i], "r");
			if (!fp || run(fp) == -1)
				fprintf(stderr, "map error\n");
			if (fp)
				fclose(fp);
			if (i < argc - 1)
				fprintf(stdout, "\n");
			i++;
		}
	}
	return (0);
}

/*
cc -Wall -Wextra -Werror -o bsq bsq.c
*/