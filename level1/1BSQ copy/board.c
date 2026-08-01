#include "bsq.h"
// 0128
char **alloc_board(int h, int w, char obstacle)
{
	char **board = (char **)malloc(sizeof(char*) * (h + 2));
	if (!board)
		return (free_board(board, h));
	for (int i = 0; i < h + 2 ; i++)
	{
		board[i] = (char *)malloc(w + 3);
		if (!board[i])
			return (free_board(board, i));
		for (int j =0; j < w + 2; j ++)
			board[i][j] = obstacle;
			// board[i][j] = '0' + j;
		board[i][w + 2] = '\0';
	}
	return board;
}

int print_board(char** board, int h ,int w)
{
	(void)w;
	for (int i = 0; i < h + 2 ; i++)
	{
		fprintf(stdout, "%s\n", board[i]);
	}
	return (0);
}

char **free_board(char** board, int h)
{
	if (!board)
		return NULL;
	for (int i = 0; i < h + 2 ; i++)
	{
		if (!board[i])
		  	return (free(board),NULL);
		free(board[i]);
	}
	return (free(board),NULL);
}
/*
  12
 01234
0....n 
1....n 1
2....n 2
3....n


*/
