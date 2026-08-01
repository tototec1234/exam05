# Life / BSQ 対試験リファクタ分析

試験で手書きする前提。実ファイル共有はできない。  
**暗記用に同じパターン・同じ関数形を両方に使う**のが目標。

---

## 0. 許可関数（必ず分ける）


| 用途    | Life                                     | BSQ                                                 | 共用できるか         |
| ----- | ---------------------------------------- | --------------------------------------------------- | -------------- |
| 確保・解放 | `malloc` / `calloc` / `realloc` / `free` | 同じ                                                  | **共用パターン可**    |
| 数値変換  | `atoi`                                   | なし（`fscanf`）                                        | 不可             |
| 入力    | `read`                                   | `fopen` / `fclose` / `getline` / `fscanf` / `stdin` | **別物**         |
| 出力    | `putchar`                                | `fputs` / `fprintf` / `stdout` / `stderr`           | **別物**（形だけ揃える） |
| その他   | —                                        | `errno`                                             | BSQのみ          |


**結論:** 共用は「盤面の確保・解放・二重ループ・座標アクセス・構造体の形」に限る。I/O は課題ごとに別暗記。

---

## 1. 両課題の共通骨格

どちらも本質は同じ。

```
1. 盤面を持つ (w, h, board)
2. 盤面を埋める / 読む
3. 二重ループで各マスを処理する
4. 結果を出力する
5. free する
```


| 段階  | Life                       | BSQ                 |
| --- | -------------------------- | ------------------- |
| 盤面  | `w h iter` + board         | `w h` + grid + 記号3つ |
| 入力  | pen (`x,y,draw`) + `wasdx` | ヘッダ1行 + map行        |
| 処理  | 隣人カウント → 世代更新              | DP → 最大正方形          |
| 出力  | 全マス `putchar`              | 塗りつぶし後 `fputs`      |


---



## 2. 現状コードの問題（試験視点）



### Life

- `t_game` に pen 座標まで入っており、覚えるフィールドが多い
- `alive = '0'` → subject は `'O'`（バグ）
- `fill` / `neighbors` / `play` / `print` / `free` / `init` で関数が多すぎる
- `play` の malloc 失敗時、途中行の free 漏れがある
- switch + flag は長い



### BSQ

- 構造体が3つ（`t_elements` / `t_map` / `t_square`）
- `ft_substr` は getline があるなら不要寄り
- `free_map` が NULL終端前提、Life の `free_board` と形が違う
- VLA `int matrix[h][w]` は大きい map で危険。試験では通ることが多いが、覚え方としては「別配列」でも可
- バリデーションが長い（ここは削りすぎ注意）

---



## 3. 共用候補の判断（質問3への回答）

判断できなかった項目を、試験優先で優先度付けする。


| パターン                             | 優先度      | 理由                                 |
| -------------------------------- | -------- | ---------------------------------- |
| `alloc_board` / `free_board`     | **必須**   | 両方で必ず書く。形を揃える価値最大                  |
| `print_board`（中身の I/O だけ差）       | **高**    | ループ形は同じ。Life=`putchar`、BSQ=`fputs` |
| `board[y][x]` または `board[y*w+x]` | **必須**   | どちらか一方に決めて両方で使う                    |
| 二重ループ `for y / for x`            | **必須**   | 処理の入口を揃える                          |
| 構造体 `w, h, board`                | **高**    | 最小共通。課題固有は外に出す                     |
| 隣人・DP・pen                        | 低（共用しない） | 課題固有ロジック                           |


**推奨する共通形（暗記コア）**

```c
typedef struct s_board {
	int		w;
	int		h;
	char	**map;   /* または char *map; （1次元） */
} t_board;

char	**alloc_board(int w, int h);   /* 失敗時 NULL */
void	free_board(char **map, int h);
void	print_board(/* Life or BSQ 用の出力 */ );
```

課題固有は構造体の外、または追加フィールドだけ。

- Life: `iter` + ローカル `x,y,draw`
- BSQ: `empty, obstacle, full` + `best_size, bi, bj`

---



## 4. 1次元 vs 2次元 比較



### 比較表


| 観点            | 2次元 `char **map`     | 1次元 `char *map`             |
| ------------- | -------------------- | --------------------------- |
| アクセス          | `map[y][x]`          | `map[y * w + x]`            |
| 暗記            | 馴染みやすい               | 式を1つ覚える必要あり                 |
| alloc         | 外側1回 + 行ごと h 回       | **1回で足りる**                  |
| free          | 行ごと + 外側             | **1回**                      |
| 試験での失敗点       | 行 malloc 失敗時の部分 free | インデックス計算ミス                  |
| Life 世代更新     | temp も2次元で同じ手間       | temp も1回 malloc             |
| BSQ DP        | `int **` or VLA 2次元  | `int *dp` で揃う               |
| 行単位 I/O (BSQ) | `fputs(map[i])` が楽   | 行ごとに書き出すか、行末に `\0` を置く工夫が要る |
| 移植しやすさ        | Life↔BSQ で感覚が近い      | 確保/解放は楽、BSQ出力が少し不利          |




### 推奨

**試験優先なら 2次元を主暗記にする。**

理由:

1. BSQ は行単位出力がある → `fputs(map[i])` がそのまま使える
2. `map[y][x]` は Life の隣人・BSQ の DP で読みやすい
3. 失敗しやすいのは「部分 free」だが、共通 `free_board(map, h)` を暗記すれば潰せる

1次元は「alloc/free を最短にしたい」「Life だけ」なら有利。  
**両方を同じ形で覚えるなら 2次元の方が総コストが低い。**

ただし雛形は両方載せる（後述）。試験当日は **どちらか一方だけ** 使う。

---



## 5. 関数の切り方（3つ前後）

Life / BSQ ともに「主処理3 + 共用ユーティリティ」に寄せる。

### 共用ユーティリティ（両課題で同じ形）

1. `alloc_board`
2. `free_board`
3. （任意）`print` のループ骨格



### Life（課題固有3）

1. `draw_pen` … stdin から wasdx で初期盤面
2. `step` … 1世代進める（neighbors は中にインライン可）
3. `main` … 引数・ループ・出力

neighbors を独立関数にするかは任意。短いなら `step` 内に書く方が暗記量が減る。

### BSQ（課題固有3）

1. `parse` … ヘッダ + map 読込 + 簡易バリデーション
2. `solve` … DP + 最大正方形記録 + 塗りつぶし
3. `main` … argc 分岐・ファイル/stdin・map error

---



## 6. リファクタ後の擬似コード



### 6.1 共通: 2次元盤面

```c
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
		map[y] = malloc(w + 1); /* Lifeは w だけでも可。BSQは行末'\0'用に +1 */
		if (!map[y])
		{
			free_board(map, y); /* 確保済み行だけ解放 */
			return (NULL);
		}
		/* 必要なら初期化: 空白埋め or '\0' */
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
```

**Life 注意:** 許可に `putchar` のみ。行は `\0` 不要でもよい。  
**BSQ 注意:** `fputs` するなら各行を `\0` 終端にする。

---



### 6.2 共通: 1次元盤面（代替雛形）

```c
char	*alloc_board_1d(int w, int h)
{
	return (calloc(w * h, 1)); /* または malloc + 手で埋める */
}

void	free_board_1d(char *map)
{
	free(map);
}

/* アクセス */
/* map[y * w + x] */
```

BSQ で `fputs` したい場合の選択肢:

- 行ごとに一時バッファへコピーして出す
- または最初から `char **` のままにする（1次元の不利点）

---



### 6.3 Life（2次元・試験用短縮形）

```c
/* life: atoi, read, putchar, malloc, free のみ */

char	**alloc_board(int w, int h);
void	free_board(char **map, int h);

void	draw_pen(char **map, int w, int h)
{
	char	c;
	int		x = 0;
	int		y = 0;
	int		pen = 0;

	while (read(0, &c, 1) == 1)
	{
		if (c == 'w' && y > 0) y--;
		else if (c == 's' && y < h - 1) y++;
		else if (c == 'a' && x > 0) x--;
		else if (c == 'd' && x < w - 1) x++;
		else if (c == 'x') pen = !pen;
		else continue;
		if (pen)
			map[y][x] = 'O';
	}
}

int	count(char **map, int w, int h, int y, int x)
{
	int	n = 0;
	int	dy, dx, ny, nx;

	for (dy = -1; dy <= 1; dy++)
		for (dx = -1; dx <= 1; dx++)
		{
			if (dy == 0 && dx == 0) continue;
			ny = y + dy;
			nx = x + dx;
			if (ny >= 0 && nx >= 0 && ny < h && nx < w
				&& map[ny][nx] == 'O')
				n++;
		}
	return (n);
}

int	step(char **map, int w, int h) /* 戻り値: 新mapを返す設計でも可 */
{
	char	**next;
	int		y, x, n;

	next = alloc_board(w, h);
	if (!next) return (-1);
	for (y = 0; y < h; y++)
		for (x = 0; x < w; x++)
		{
			n = count(map, w, h, y, x);
			if (map[y][x] == 'O')
				next[y][x] = (n == 2 || n == 3) ? 'O' : ' ';
			else
				next[y][x] = (n == 3) ? 'O' : ' ';
		}
	/* 呼び出し側で free(map); map = next; */
	return (0); /* 実装時は next を返す方が単純 */
}

void	print_board(char **map, int w, int h)
{
	int	y, x;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
			putchar(map[y][x]);
		putchar('\n');
	}
}

int	main(int argc, char **argv)
{
	int		w, h, iter, i;
	char	**map;
	char	**next;

	if (argc != 4) return (1);
	w = atoi(argv[1]);
	h = atoi(argv[2]);
	iter = atoi(argv[3]);
	map = alloc_board(w, h);
	if (!map) return (1);
	/* 全マス ' ' で初期化（alloc内でも可） */
	draw_pen(map, w, h);
	for (i = 0; i < iter; i++)
	{
		next = /* step が char** を返す */;
		if (!next) { free_board(map, h); return (1); }
		free_board(map, h);
		map = next;
	}
	print_board(map, w, h);
	free_board(map, h);
	return (0);
}
```

**Life ルール圧縮（どちらでも可）**

```c
/* 生きてる: 隣人2or3 / 死んでる: 隣人3 */
alive = (map[y][x] == 'O');
next[y][x] = ((alive && (n == 2 || n == 3)) || (!alive && n == 3)) ? 'O' : ' ';
```

---



### 6.4 BSQ（2次元・試験用短縮形）

```c
/* bsq: malloc/free, fopen/fclose, getline, fscanf, fputs, fprintf, stdin/stdout/stderr */

char	**alloc_board(int w, int h); /* 各行 w+1、末尾 '\0' */
void	free_board(char **map, int h);

int	parse(FILE *fp, char ***map, int *w, int *h,
		char *empty, char *obst, char *full)
{
	/* fscanf で n empty obst full */
	/* getline で各行読み、長さチェック、文字チェック */
	/* *map = alloc... に行コピー */
	/* 失敗時 -1 */
}

void	solve(char **map, int w, int h, char empty, char obst, char full)
{
	int	dp[h][w]; /* または int *dp = calloc(w*h, sizeof(int)); */
	int	best = 0, bi = 0, bj = 0;
	int	y, x, m;

	for (y = 0; y < h; y++)
		for (x = 0; x < w; x++)
		{
			if (map[y][x] == obst)
				dp[y][x] = 0;
			else if (y == 0 || x == 0)
				dp[y][x] = 1;
			else
			{
				m = dp[y-1][x];
				if (dp[y-1][x-1] < m) m = dp[y-1][x-1];
				if (dp[y][x-1] < m) m = dp[y][x-1];
				dp[y][x] = m + 1;
			}
			if (dp[y][x] > best)
			{
				best = dp[y][x];
				bi = y - best + 1;
				bj = x - best + 1;
			}
		}
	for (y = bi; y < bi + best; y++)
		for (x = bj; x < bj + best; x++)
			map[y][x] = full;
}

void	print_board(char **map, int h)
{
	int	y;

	for (y = 0; y < h; y++)
	{
		fputs(map[y], stdout);
		fputc('\n', stdout);
	}
}

int	run(FILE *fp)
{
	char	**map;
	int		w, h;
	char	e, o, f;

	if (parse(fp, &map, &w, &h, &e, &o, &f) == -1)
		return (-1);
	solve(map, w, h, e, o, f);
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
		for (i = 1; i < argc; i++)
		{
			fp = fopen(argv[i], "r");
			if (!fp || run(fp) == -1)
				fprintf(stderr, "map error\n");
			if (fp) fclose(fp);
			if (i < argc - 1)
				fprintf(stdout, "\n");
		}
	}
	return (0);
}
```

---



## 7. 暗記チェックリスト（当日用）



### 共通（先に書く）

- [ ] `alloc_board(w,h)` + 失敗時 `free_board(map, 確保済み行数)`
- [ ] `free_board(map, h)`
- [ ] 二重ループ `y` → `x`、アクセス `map[y][x]`



### Life だけ

- [ ] `argc == 4`、`atoi` で w/h/iter
- [ ] pen: `x,y,pen` ローカル、`wasd` 移動、`x` トグル、pen中は `'O'`
- [ ] 隣人8方向、盤外は死
- [ ] 生存: 2or3 / 誕生: 3、文字は `'O'` と `' '`
- [ ] 出力は `putchar` のみ



### BSQ だけ

- [ ] ヘッダ `fscanf`、map は `getline`
- [ ] 行長一致・文字は empty/obst のみ・記号重複NG
- [ ] DP: obst=0、端=1、それ以外 min(上,左,左上)+1
- [ ] 最大更新時は左上座標 `y-size+1, x-size+1`
- [ ] 塗りつぶし → `fputs`、エラーは `fprintf(stderr, "map error\n")`
- [ ] 複数ファイルは解答/エラーのあと空行

---



## 8. 最終推奨（この分析の結論）


| 項目      | 推奨                                                                     |
| ------- | ---------------------------------------------------------------------- |
| ファイル    | 各課題1ファイルでよい（`.h` は最小 or なしでも可。expected は `*.c *.h` なので空でも `.h` を出す想定で） |
| 盤面表現    | **2次元** `char `** **を主暗記**。1次元は予備知識                                    |
| 構造体     | `w,h,map` 最小。Life の pen はローカル。BSQ 記号はローカル or 小さな struct                |
| 共用      | `alloc_board` / `free_board` / 二重ループ形を同一にする                            |
| I/O     | 共用しない。Life=`read`/`putchar`、BSQ=`getline`/`fscanf`/`fputs`             |
| 関数数     | 共用2 + 課題固有おおむね3                                                        |
| Life 修正 | `alive` を `'O'` に直す                                                    |


---



## 9. 次の実装ステップ（この md の後）

1. Life を上記短縮形でリファクタ（動作確認）
2. BSQ を同じ `alloc_board` / `free_board` 形にリファクタ
3. 両方を眺めて「同じ行が並んでいるか」を確認し、ズレたら揃える

実装に進むときは、Life から / BSQ から / 同時、のどれかを指定する。