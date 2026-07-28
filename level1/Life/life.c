#include "life.h"
void	draw_pen(char **map, int w, int h)
{
	char	c;
	int		x = 1, y = 1, pen = 0;

	while (read(0, &c, 1) == 1)
	{
		if (c == 'w' && y > 1)
			y--;
		else if (c == 's' && y < h)
			y++;
		else if (c == 'a' && x > 1)
			x--;
		else if (c == 'd' && x < w)
			x++;
		else if (c == 'x')
			pen = !pen;
		else
			continue ;
		if (pen)
			map[y][x] = 'O';
	}
}
int	count_nb(char **map, int y, int x)
{
	int	n = 0;
	for (int dy = -1; dy <= 1; dy++)
		for (int dx = -1; dx <= 1; dx++)
			if (!(dy == 0 && dx == 0) && map[y + dy][x + dx] == 'O')
				n++;
	return (n);
}

char	**step(char **map, int w, int h)
{
	char	**next = alloc_board(w, h);
	if (!next)
		return (NULL);
	for (int y = 1; y <= h; y++)
		for (int x = 1; x <= w; x++)
		{
			int n = count_nb(map, y, x);
			int alive = (map[y][x] == 'O');
			if ((alive && (n == 2 || n == 3)) || (!alive && n == 3))
				next[y][x] = 'O';
			else
				next[y][x] = ' ';
		}
	return (next);
}

void	print_board(char **map, int w, int h)
{
	for (int y = 1; y <= h; y++)
	{
		for (int x = 1; x <= w; x++)
			putchar(map[y][x]);
		putchar('\n');
	}
}

int	main(int argc, char **argv)
{
	char	**next;

	if (argc != 4)
		return (1);
	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int iter = atoi(argv[3]);
	char **map = alloc_board(w, h);
	if (!map)
		return (1);
	draw_pen(map, w, h);
	for (int i = 0; i < iter; i++)
	{
		next = step(map, w, h);
		free_board(map, h + 2);
		if (!next)
			return (1);
		map = next;
	}
	print_board(map, w, h);
	free_board(map, h + 2);
	return (0);
}

/*
cc -Wall -Wextra -Werror -o life board.c life.c
echo 'sdxddssaaww' | ./life 5 5 0
*/
