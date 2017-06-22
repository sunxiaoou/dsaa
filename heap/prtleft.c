#include <stdio.h>
#include <stdlib.h>

#include "leftheap.h"

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

void PrintTree(PriorityQueue T, int depth)
{
	static int col;
	static int bufsize;
	static ArrayD *buffer;
	int i;

	if (! T)
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

    PrintTree(T->Left, depth + 1);
	appendArray(&buffer[depth], T->Element, col);
	col += 2;
    PrintTree(T->Right, depth + 1);

	if (! depth) {
		printAll(buffer, bufsize);
		printf("\n");
		free(buffer);
	}
}
