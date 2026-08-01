#include "bsq.h"

int main(int ac, char **av)
{
	FILE *fp;

	if (ac == 1)
	{
		if (run(stdin) == -1)
			fprintf(stderr, "map error\n");
		return (0);
	}
	for (int i = 1; i < ac; i++)
	{
		fp = fopen(av[i], "r");
		if (!fp || run(fp) == -1)
			fprintf(stderr, "map error\n");
		if (fp)
			fclose(fp);
		if (ac > 2)
			fprintf(stdout, "\n");
	}
	return (0);
}

/*
	cc main.c bsq.c board.c -Wall -Wextra -Werror
*/
