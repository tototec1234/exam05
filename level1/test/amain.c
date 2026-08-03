#include "a.h"

static int sovl(char** map, int h,  int w,  char o,  char e,  char f)
{
	int dp[h + 2][w + 2];


}

static int pppp(FILE* fp, char*** map, int *h, int *w, char* e, char* o, char* f)
{
	if (fscanf(fp, "%d %c %c %c", h, e, o, f) != 4)
		return (printf("FSCANF error"), 1);
	printf("%d %c %c %c\n", *h, *e, *o, *f);

	char *line = NULL;
	int len;
	size_t cap = 0;

	if (getline(&line, &cap,fp) < 0)
		return (printf("READ error"), 1);

	for (int y = 1; y <= *h ; y++)
	{
		len = (int)getline(&line, &cap,fp) - 1;

		if (y == 1)
		{
			// len = (int)getline(&line, &cap,fp) - 1;
			*w = len;
			*map = map_alloc(*h, *w, *f);	
		}
		if (*w != len)
			return (printf("READtoryu error"), 1);
		for (int x = 1; x < *w + 1; x++)
		{
			printf("[%d]line[%d - 1][%c]\n", y, x, line[x - 1]);
			(*map)[y][x] = line[x - 1];
		}

		
	}
	free(line);

	return 0;	
}


static int run(FILE* fp)
{
	int h, w;
	char e, o, f;
	char** map = NULL;

	pppp (fp, &map, &h, &w, &o, &e, &f);
	
	map_print(map, h + 1, w + 1);
	sovl(map, h, w, o, e, f);
	map_free(map, h);
	
	return 0;
}


int main(int ac, char** av)
{
	FILE* fp;

	if (ac == 1)
		return (run(stdin));
	for (int i = 1; i < ac; i++)
	{
		fp = fopen(av[i], "r");
		if (fp < 0)
			printf("FP error ");
		run(fp);
	}
	return 0;
}



