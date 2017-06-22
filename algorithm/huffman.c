#include <stdio.h>
#include <stdlib.h>

#include "hufftree.h"
#include "prttree.h"
#include "binheap.h"


int valueOfTree(void *t)
{
	return ((HuffPtr)t)->C->value;
}

int compareTree(void *a, void *b)
{
	if (! a || ! b)
		return 0;

	return ((HuffPtr)a)->C->frequency - ((HuffPtr)b)->C->frequency;
}

void Huffman(Character chs[], int num)
{
	int i;
	HuffPtr A, B;
	PriorityQueue H;

	H = CreateHeap(num);
	H->pValue = valueOfTree;
	H->pCompare = compareTree;

	for (i = 0; i < num; i ++)
		InsertHeap(InitTree(&chs[i]), H);
		
	while ((A = DeleteHeap(H)) && (B = DeleteHeap(H)))
		InsertHeap(MergeTree(A , B), H);
		
	pTNode = valueOfTree;
	DrawTree((TreePtr)A, 0);
	EncodeTree(A, NULL, 0);
}


main()
{
	static Character chs[] = {
		'a', "", 10, 0,
		'e', "", 15, 0,
		'i', "", 12, 0,
		's', "", 3, 0,
		't', "", 4, 0,
		' ', "", 13, 0,
		'\n', "", 1, 0
	};
	int i, num;
	long sum;

	num = sizeof(chs) / sizeof(*chs);
	Huffman(chs, num);

	sum = 0;
	for (i = 0; i < num; i++) {
		sum += chs[i].totalbits;
		printf("%02x %8s %02d %04d\n",
		   	chs[i].value, chs[i].code, chs[i].frequency, chs[i].totalbits);
	}

	printf("\nTotal %ld bits.\n", sum);
}
