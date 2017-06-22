#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hufftree.h"

HuffPtr InitTree(CharPtr C)
{
	HuffPtr T;

	T = malloc(sizeof(struct HuffNode));
	assert(T);

	T->C = C;
	T->Left = T->Right = NULL;

	return T;
}

HuffPtr MergeTree(HuffPtr A, HuffPtr B)
{
	CharPtr C;
	HuffPtr T;

	T = malloc(sizeof(struct HuffNode));
	assert(T);

	C = malloc(sizeof(struct Character));
	assert(C);

	C->value = 0;
	C->frequency = A->C->frequency + B->C->frequency;
	T->C = C;
	T->Left = A;
	T->Right = B;

	return T;
}

void EncodeTree(HuffPtr T, char *code, int isRight)
{
	int i, size;

	if (! T)
		return;

	size = sizeof(T->C->code) - 1;
	if (! code)
		memset(T->C->code, ' ', size);
	else {
		memcpy(T->C->code, code + 1, size - 1);
		if (! isRight)
			T->C->code[size - 1] = '0';
		else
			T->C->code[size - 1] = '1';
	}
	T->C->code[size] = 0;

	if (T->C->value) {
		for (i = 0; T->C->code[i] == ' '; i ++)
			size --;
		T->C->totalbits = size * T->C->frequency;
	}

	EncodeTree(T->Left, T->C->code, 0);
	EncodeTree(T->Right, T->C->code, 1);
}
