#include "bsq.h"
#include <stdio.h>
// 0128
// 0234
// 2015
// 2025  
int main(int ac, char** av)
{
	FILE *fp;
	if (ac == 1)
		if (run(stdin) == -1)
			return (fprintf(stderr, "map error\n") , 0);
	
	for (int i = 1; i < ac ; i++)
	{
		fp = fopen(av[i], "r");
		if (!fp || run(fp) == -1)
			fprintf(stderr, "map error\n");
			// fprintf(stderr, "map error");

		if (fp)
			fclose(fp);
		if ( ac > 2)
			fprintf(stdout, "\n");
	}
	return 0;
}

/*
 cc main.c bsq.c bsq.h board.c -Wall -Wextra -Werror

	int h = atoi(av[1]);
	int w = atoi(av[2]);
	if (h < 1 || w < 1)
		return 1;
	char o = (char)av[3][0];
	char** map = alloc_board(h, w, o);
	if (map)
		print_board(map, h, w);
	free_board(map, h, w);
	
*/
/*
ac 1 2 3
av 0 1 2

  12
 01234
0....n 
1....n 1
2....n 2
3....n


*/
