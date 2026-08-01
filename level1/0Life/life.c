#include "life.h"
#include <algorithm>
#include <stdio.h>



void draw_pen(char **map, int w, int h)
{
	char c;
	int x = 1, y=1, pen =0;

	while(read(0, &c, 1 )==1)
	{
		if (c)
	}
}

void print_board(char **map, int w, int h)
{
	for (int y=1; y <=h ; y++)
	{
		for (int x=1; x <=w ; x++)
			putchar(map[y][x]);
		putchar('\n');
	}
}

int count_nb(char **map, int y, int x){
	int n =0;
	for (int dy =-1; dy <=1 ; dy++)

}

char **step(char **map, int w, int h)
{
	char **next = alloc_board(w,h);
	for (int y = 1 ; y <= h)
}

int main(int ac, char** av)
{
	if (ac != 4)
		return 1;
	int w = atoi(av[1]);
	int h = atoi(av[2]);
	int iter = atoi(av[3]);
	char **map = alloc_board(w , h);
	if (!map)
		return 1;
	draw_pen(map, w, h);
	for (int i = 0; i < iter; i++)
	{
		next = step(map, w, h);
		free_board(map, h + 2);
		if (!next)
			return(1);
		map = next;
	}
	print_board(map, w, h);
	free_board(map, h + 2);
	return 0;
}