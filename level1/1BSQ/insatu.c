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
#include "bsq.h"

/* 盤面は四辺に障害物の番兵を1マス持つ (h + 2) 行 x (w + 2) 列。
   各行は末尾の '\0' を含めて w + 3 バイト確保する。 */
char **alloc_board(int h, int w, char obstacle)
{
	char **board = (char **)calloc(h + 2, sizeof(char *));

	if (!board)
		return (NULL);
	for (int i = 0; i < h + 2; i++)
	{
		board[i] = (char *)calloc(w + 3, sizeof(char));
		if (!board[i])
			return (free_board(board, h));
		for (int j = 0; j < w + 2; j++)
			board[i][j] = obstacle;
	}
	return (board);
}

/* デバッグ用。番兵の枠を含めた盤面全体を表示する。 */
int print_board(char **board, int h, int w)
{
	for (int i = 0; i < h + 2; i++)
		fprintf(stdout, "%.*s\n", w + 2, board[i]);
	return (0);
}

char **free_board(char **board, int h)
{
	if (!board)
		return (NULL);
	for (int i = 0; i < h + 2; i++)
		free(board[i]);
	return (free(board), NULL);
}
