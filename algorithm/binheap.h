#ifndef _BinHeap_H
#define _BinHeap_H

typedef void* ElementType;

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
	int (*pValue)(ElementType);
	int (*pCompare)(ElementType, ElementType);
};

typedef struct HeapStruct *PriorityQueue;


PriorityQueue CreateHeap(int num);
void DestroyHeap(PriorityQueue H);
int BuildHeap(void *array, int size, int num, PriorityQueue H);
void EmptyHeap(PriorityQueue H);
int IsHeapEmpty(PriorityQueue H);
int IsHeapFull(PriorityQueue H);
int InsertHeap(ElementType X, PriorityQueue H);
ElementType DeleteHeap(PriorityQueue H);

// void PrintTree(PriorityQueue H, int tree);
#endif
