#include "bsq.h"

/* 盤面は四辺に fill の番兵を1マス持つ (h + 2) 行 x (w + 2) 列。
   各行は末尾の '\0' を含めて w + 3 バイト確保する。 */
char **alloc_board(int h, int w, char fill)
{
	char **board = (char **)calloc(h + 2, sizeof(char *));

	if (!board)
		return (NULL);
	for (int y = 0; y < h + 2; y++)
	{
		board[y] = (char *)calloc(w + 3, sizeof(char));
		if (!board[y])
			return (free_board(board, h));
		for (int x = 0; x < w + 2; x++)
			board[y][x] = fill;
	}
	return (board);
}

/* デバッグ用。番兵の枠を含めた盤面全体を表示する。 */
int print_board(char **board, int h, int w)
{
	for (int y = 0; y < h + 2; y++)
		fprintf(stdout, "%.*s\n", w + 2, board[y]);
	return (0);
}

char **free_board(char **board, int h)
{
	if (!board)
		return (NULL);
	for (int y = 0; y < h + 2; y++)
		free(board[y]);
	return (free(board), NULL);
}
