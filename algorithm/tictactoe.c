#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOARDSIZE 9
#define SPACE '_'

#define COMPWIN 1
#define DRAW 0
#define COMPLOSS -1

int fullBoard(char board[])
{
	int i;

	for (i = 0; i < BOARDSIZE; i ++)
		if (board[i] == SPACE)
			return 0;

	return 1;
}

int immediateWin(char board[], char c, int *bestMove)
{
	static int lines[][3] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8,	/* rows */
		0, 3, 6, 1, 4, 7, 2, 5, 8,	/* cols */
		0, 4, 8, 2, 4, 6			/* cross */
	};
	int i, j;
	int o, x, b;

	for (j = 0; j < sizeof(lines) / sizeof(*lines); j ++) {
		for (i = o = x = 0; i < 3; i ++) {
			if (board[lines[j][i]] == 'O') 
				o ++;
			else if (board[lines[j][i]] == 'X')
				x ++;
			else
				b = i;
		}	
		if ((c == 'O' && (o == 2 && ! x)) || (c == 'X' && (x == 2 && ! o))) {
			*bestMove = lines[j][b];
			return 1;			
		}
	}
			
	return 0;
}

int isWin(char board[], char c)
{
	static int lines[][3] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8,	/* rows */
		0, 3, 6, 1, 4, 7, 2, 5, 8,	/* cols */
		0, 4, 8, 2, 4, 6			/* cross */
	};
	int i, j;
	int o, x;

	for (j = 0; j < sizeof(lines) / sizeof(*lines); j ++) {
		for (i = o = x = 0; i < 3; i ++) {
			if (board[lines[j][i]] == 'O') 
				o ++;
			else if (board[lines[j][i]] == 'X')
				x ++;
		}	
		if ((c == 'O' && o == 3) || (c == 'X' && x == 3))
			return 1;			
	}
			
	return 0;
}

int isEmpty(char board[], int i)
{
	return board[i] == SPACE;
}

void place(char board[], int i, char c)
{
	board[i] = c;
}

void unplace(char board[], int i)
{
	board[i] = SPACE;
}

void findHumanMove(char board[], int *bestMove, int *value);

void findCompMove(char board[], int *bestMove, int *value)
{
	int dc, i, response;	/* dc means don't care */

	if (fullBoard(board))
		*value = DRAW;
	else if (immediateWin(board, 'O', bestMove))
		*value = COMPWIN;
	else {
		*value = COMPLOSS;
		for (i = 0; i < BOARDSIZE; i ++) { /* try each square */
			if (isEmpty(board, i)) {
				place(board, i, 'O');
				findHumanMove(board, &dc, &response);
				unplace(board, i);
				if	(response > *value) {	/* Update best move */
					*value = response;
					*bestMove = i;
				}
			}
		}
	}
}

void findHumanMove(char board[], int *bestMove, int *value)
{
	int dc, i, response;	/* dc means don't care */

	if (fullBoard(board))
		*value = DRAW;
	else if (immediateWin(board, 'X', bestMove))
		*value = COMPLOSS;
	else {
		*value = COMPWIN;
		for(i = 0; i < BOARDSIZE; i ++) {	/* try each square */
			if (isEmpty(board, i)) {
				place(board, i, 'X');
				findCompMove(board, &dc, &response);
				unplace(board, i);
				if (response < *value) {	/* Update best move */
					*value = response;
					*bestMove = i;
				}
			}
		}
	}
}

void printBoard(char board[])
{
	int i;

	for (i = 0; i < BOARDSIZE; i ++) {
		if (i && ! (i % 3))
			putchar('\n');
		putchar(board[i]);
		putchar(' ');
	}

	printf("\n\n");
}

int getnum(char *title)
{
	char tmp[80];

	printf("%s: ", title);
	fgets(tmp, sizeof(tmp), stdin);

	return atoi(tmp) - 1;
}

int main(int argc, char *argv[])
{
	char board[BOARDSIZE];
	int a, i, m, v;

	if (argc < 2) {
		printf("%s 0|1 (Computer|Human first)\n", argv[0]);
		exit(1);
	}

	a = (atoi(argv[1]) == 1);

//	memcpy(board, "__OX_OXOX", BOARDSIZE);
	memset(board, SPACE, sizeof(board));

/*
	for (i = 0; (! fullBoard(board)); i ++) {
		if (! (i % 2)) {
			findCompMove(board, &m, &v);
			printf("%02d: Comp %d %d\n", i, m, v);
			place(board, m, 'O');
		}
		else {
			findHumanMove(board, &m, &v);
			printf("%02d: Human %d %d\n", i, m, v);
			place(board, m, 'X');
		}
		printBoard(board);
	}
*/

	printBoard(board);
	for (i = 0; (! fullBoard(board)); i ++) {
		if (i % 2 == a) {
			printf("Computer's turn:\n");
			findCompMove(board, &m, &v);
			printf("%02d: Comp %d %d\n", i, m, v);
			place(board, m, 'O');
			printBoard(board);
			if (isWin(board, 'O')) {
				printf("Computer Win!\n");
				exit(0);
			}
		}

		else {
			do {
				m = getnum("Your Turn, please input 1-9");
			} while ((m < 0 || m > 8) || (! isEmpty(board, m)));
			printf("%02d: Human %d %d\n", i, m, v);
			place(board, m, 'X');
			printBoard(board);
			if (isWin(board, 'X')) {
				printf("You Win!\n");
				exit(0);
			}
		}
	}

	printf("We tie!\n");	
}
