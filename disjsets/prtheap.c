#include <stdio.h>
#include <stdlib.h>

#include "binheap.h"

typedef struct dot {
	int val;
	int col;
} DOT;

typedef struct {
	int idx;
	DOT dot[100];
} ArrayD;

void appendArray(ArrayD *a, int v, int c)
{
	if (a->idx == 79) {
		printf("overflow max column\n");
		return;
	}

	a->dot[a->idx].val = v;
	a->dot[a->idx].col = c;

	a->idx ++;
}

void printArray(ArrayD *a)
{
	int i, j;
	int off = 0;

	for (j = 0; j < a->idx; j ++) {
		for (i = 0; i < a->dot[j].col - off; i ++)
			putchar(' ');
		printf("%02d", a->dot[j].val);
		off = a->dot[j].col + 2;
	}

	printf("\n");
}

void printAll(ArrayD *buf, int num)
{
	int i;

	for (i = 0; i < num; i ++) {
		if (buf[i].idx)
			printArray(&buf[i]);
	}
}

int log_2(int x)
{
	int i;

	for (i = 0; x ; i ++)
		x >>= 1;

	return i - 1;
}

void PrintTree(PriorityQueue H, int tree)
{
	static int col;
	static int bufsize;
	static ArrayD *buffer;
	int i, depth;

	if (tree > H->Size)
		return;

	if (tree == 1) {
		col = 0;
		bufsize = 0;
		buffer = NULL;
	}

	depth = log_2(tree);
	if (bufsize < depth + 1) {
		i = bufsize;
		bufsize += 10;
		buffer = realloc(buffer, sizeof(ArrayD) * bufsize);
		for (; i < bufsize; i ++)
			buffer[i].idx = 0;
	}

	PrintTree(H, tree * 2);
	appendArray(&buffer[depth], H->pValue(H->Elements[tree]), col);
	col += 2;
	PrintTree(H, tree * 2 + 1);

	if (tree == 1) {
		printAll(buffer, bufsize);
		printf("\n");
		free(buffer);
	}
}
