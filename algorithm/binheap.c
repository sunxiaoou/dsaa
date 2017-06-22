#include "binheap.h"
#include "fatal.h"
#include <string.h>
#include <stdlib.h>

#define MinPQSize (10)
// #define MinData (-32767)

PriorityQueue CreateHeap(int num)
{
	int i;
	PriorityQueue H;

	num = num < MinPQSize ? MinPQSize : num;

	H = malloc(sizeof(struct HeapStruct));
	if (! H)
		FatalError( "Out of space!!!" );

/* Allocate the array plus one extra for sentinel */
	H->Elements = malloc((num + 1) * sizeof(ElementType));
	if (! H->Elements)
		FatalError( "Out of space!!!" );

	H->Capacity = num;
	H->Size = 0;
/* H->Element[0] is a sentinel */
	H->Elements[0] = NULL;

	return H;
}

void DestroyHeap(PriorityQueue H)
{
	free(H->Elements);
	free(H);
}

static void percolateDown(int idx, PriorityQueue H)
{
	int i, Child;
	ElementType tmp;

	for (i = idx; i * 2 <= H->Size; i = Child) {
		Child = i * 2;
		if (Child != H->Size &&
		   	H->pCompare(H->Elements[Child + 1], H->Elements[Child]) < 0)
			Child ++;

		if (H->pCompare(H->Elements[Child], H->Elements[i]) < 0) {
			tmp = H->Elements[i];
			H->Elements[i] = H->Elements[Child];
			H->Elements[Child] = tmp;
		}
	}			
}

int BuildHeap(void *array, int size, int num, PriorityQueue H)
{
	int i;

	if (num > H->Capacity) {
		printf("Out of queue capacity\n");
		return -1;
	}

	for (i = 0; i < num; i ++)
		H->Elements[i + 1] = (char *)array + i * size;

	H->Size = num;

	for (i = H->Size / 2; i > 0; i --)
		percolateDown(i, H);

	return 0;
}

void EmptyHeap(PriorityQueue H)
{
	H->Size = 0;
}

int IsHeapEmpty(PriorityQueue H)
{
	return H->Size == 0;
}

int IsHeapFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}

int InsertHeap(ElementType X, PriorityQueue H)
{
	int i;

	if (IsHeapFull(H)) {
		Error( "Priority queue is full" );
		return -1;
	}

	for (i = ++ H->Size; H->pCompare(H->Elements[i / 2], X) > 0; i /= 2)
		H->Elements[i] = H->Elements[i / 2];

	H->Elements[i] = X;

	return 0;
}

ElementType DeleteHeap(PriorityQueue H)
{
	int i, Child;
	ElementType MinElement, LastElement;

	if (IsHeapEmpty(H)) {
//		Error( "Priority queue is empty" );
		return NULL;
	}

	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size --];

	for(i = 1; i * 2 <= H->Size; i = Child) {
		/* Find smaller child */
		Child = i * 2;
		if (Child != H->Size &&
		   	H->pCompare(H->Elements[Child + 1], H->Elements[Child]) < 0)
			Child ++;

		/* Percolate one level */
		if (H->pCompare(LastElement, H->Elements[Child]) > 0)
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}

	H->Elements[i] = LastElement;

	return MinElement;
}


#ifdef MYTEST

int valueOfElement(ElementType e)
{
	return *(int *)e;
}

int compareElement(ElementType a, ElementType b)
{
	if (! a || ! b)
		return 0;

	return *(int *)a - *(int *)b;
}

main()
{
	static int a[] = {
		150, 80, 40, 30, 10, 70, 110,
	   	100, 20, 90, 60, 50, 120, 140, 130
	};
		
	int i;
	int x[20];
	PriorityQueue H;

	H = CreateHeap(100);
	H->pValue = valueOfElement;
	H->pCompare = compareElement;

	for (i = 0; i < 20; i ++)  {
		x[i] = rand() % 100;
        InsertHeap(&x[i], H);
		printf("insert %d\n", x[i]);
		PrintTree(H, 1);
	}

    while(! IsHeapEmpty(H)) {
		printf("delete %d\n", *(int *)DeleteHeap(H));
		PrintTree(H, 1);
	}

	printf("\n");
	BuildHeap(a, sizeof(int), sizeof(a) / sizeof(*a), H);
	PrintTree(H, 1);
}
#endif
