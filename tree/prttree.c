#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "prttree.h"

typedef struct dot {
	char val[8];
	int col;
} DOT;

typedef struct {
	int idx;
	DOT dot[100];
} ArrayD;

static void appendArray(ArrayD *a, char *v, int c)
{
	if (a->idx == 79) {
		printf("overflow max column\n");
		return;
	}

	strcpy(a->dot[a->idx].val, v);
	a->dot[a->idx].col = c;

	a->idx ++;
}

static void printArray(ArrayD *a)
{
	int i, j;
	int off = 0;

	for (j = 0; j < a->idx; j ++) {
		for (i = 0; i < a->dot[j].col - off; i ++)
			putchar(' ');
		printf("%s", a->dot[j].val);
		off = a->dot[j].col + 2;
	}

	printf("\n");
}

static void printAll(ArrayD *buf, int num)
{
	int i;

	for (i = 0; i < num; i ++) {
		if (buf[i].idx)
			printArray(&buf[i]);
	}
}

void DrawTree(TreePtr T, int depth)
{
	static int col;
	static int bufsize;
	static ArrayD *buffer;
	int i;

	if ((! pNullNode && ! T) || (pNullNode && pNullNode() == T))
		return;

	if (! depth) {
		col = 0;
		bufsize = 0;
		buffer = NULL;
	}

	if (bufsize < depth + 1) {
		i = bufsize;
		bufsize += 10;
		buffer = realloc(buffer, sizeof(ArrayD) * bufsize);
		for (; i < bufsize; i ++)
			buffer[i].idx = 0;
	}

    DrawTree(T->Left, depth + 1);
	appendArray(&buffer[depth], pT2Str(T), col);
	col += 2;
    DrawTree(T->Right, depth + 1);

	if (! depth) {
		printAll(buffer, bufsize);
		printf("\n");
		free(buffer);
	}
}

void PrintTree(TreePtr T, int depth)
{
	if (! T)
		return;

	PrintTree(T->Left, depth + 1);
	printf("%s", pT2Str(T));
	PrintTree(T->Right, depth + 1);

	if (! depth)
		printf("\n");
}
