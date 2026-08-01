#include "life.h"

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

void	draw_pen(char **map, int w, int h)
{
	char	c;
	int		x;
	int		y;
	int		pen;

	x = 0;
	y = 0;
	pen = 0;
	while (read(0, &c, 1) == 1)
	{
		if (c == 'w' && y > 0)
			y--;
		else if (c == 's' && y < h - 1)
			y++;
		else if (c == 'a' && x > 0)
			x--;
		else if (c == 'd' && x < w - 1)
			x++;
		else if (c == 'x')
			pen = !pen;
		else
			continue ;
		if (pen)
			map[y][x] = 'O';
	}
}

int	count_nb(char **map, int w, int h, int y, int x)
{
	int	n;
	int	dy;
	int	dx;
	int	ny;
	int	nx;

	n = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!(dy == 0 && dx == 0))
			{
				ny = y + dy;
				nx = x + dx;
				if (ny >= 0 && nx >= 0 && ny < h && nx < w
					&& map[ny][nx] == 'O')
					n++;
			}
			dx++;
		}
		dy++;
	}
	return (n);
}

char	**step(char **map, int w, int h)
{
	char	**next;
	int		y;
	int		x;
	int		n;
	int		alive;

	next = alloc_board(w, h);
	if (!next)
		return (NULL);
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			n = count_nb(map, w, h, y, x);
			alive = (map[y][x] == 'O');
			if ((alive && (n == 2 || n == 3)) || (!alive && n == 3))
				next[y][x] = 'O';
			else
				next[y][x] = ' ';
			x++;
		}
		y++;
	}
	return (next);
}

void	print_board(char **map, int w, int h)
{
	int	y;
	int	x;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			putchar(map[y][x]);
			x++;
		}
		putchar('\n');
		y++;
	}
}

int	main(int argc, char **argv)
{
	int		w;
	int		h;
	int		iter;
	int		i;
	int		y;
	int		x;
	char	**map;
	char	**next;

	if (argc != 4)
		return (1);
	w = atoi(argv[1]);
	h = atoi(argv[2]);
	iter = atoi(argv[3]);
	map = alloc_board(w, h);
	if (!map)
		return (1);
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			map[y][x] = ' ';
			x++;
		}
		y++;
	}
	draw_pen(map, w, h);
	i = 0;
	while (i < iter)
	{
		next = step(map, w, h);
		if (!next)
		{
			free_board(map, h);
			return (1);
		}
		free_board(map, h);
		map = next;
		i++;
	}
	print_board(map, w, h);
	free_board(map, h);
	return (0);
}

/*
cc -Wall -Wextra -Werror -o life life.c 
 echo 'sdxddssaaww' | ./life 5 5 0 
*/