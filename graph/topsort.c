#include <stdio.h>
#include <stdlib.h>

#include "fatal.h"

typedef int Vertex;

typedef struct ListNode {
    Vertex V;
    struct ListNode *Next;
} ListNode, *Position, *List;

typedef struct Graph {
	int nV;
	int nE;
	List *TheLists;
} Graph, *GraPtr;


List CreateList(void)
{
	List L;

	L = malloc(sizeof(struct ListNode));
	if (! L)
		FatalError("Out of space!!!");
	else {
		L->V = 0;
		L->Next = NULL;
	}

	return L;
}

void PushList(Vertex V, List L)
{
	Position P;

	P = malloc(sizeof(struct ListNode));
	if(! P)
		FatalError("Out of space!!!");

	P->V = V;
	P->Next = L->Next;
	L->Next = P; 
}

int IsEmptyList(List L)
{
	return L->Next == NULL;
}

Vertex PopList(List L)
{
	Vertex V;	
	Position P;

	if (IsEmptyList(L))
		return -1;

	P = L->Next;
	V = P->V;
	L->Next = P->Next;
	free(P);

	return V;
}

GraPtr InitializeGraph(int edges[][2], int num)
{
	int i;
	GraPtr H;
	Position P;

	H = malloc(sizeof(struct Graph));
	if( H == NULL )
		FatalError( "Out of space!!!" );

	H->nE = num;
	for (H->nV = 0, i = 0; i < H->nE; i ++) {
		H->nV = H->nV < edges[i][0] ? edges[i][0] : H->nV;
		H->nV = H->nV < edges[i][1] ? edges[i][1] : H->nV;
	}
	H->nV ++;

	H->TheLists = malloc( sizeof( List ) * H->nV );
	if( H->TheLists == NULL )
		FatalError( "Out of space!!!" );

	for (i = 0; i < H->nV; i ++)
		H->TheLists[i] = CreateList();

	for (i = 0; i < H->nE; i ++) {
   		PushList(edges[i][1], H->TheLists[edges[i][0]]);
/* set header counter as indegree */
		H->TheLists[edges[i][1]]->V ++;
	}

	return H;
}

void PrintList(List L)
{
	int i;
	Position p;

	p = L;
	for (i = 0; p; i ++) {
		printf("%d ", p->V);
		p = p->Next;
	}
	printf("\n");
}

void PrintTable(GraPtr H)
{
	int i;

	for (i = 0; i < H->nV; i ++) {
		printf("%02d: ", i);
		PrintList(H->TheLists[i]);	
	}
}

void TopSort(GraPtr H)
{
	int i;
	int *indegree, *topsort;
	Position P;
	List L;

	L = CreateList();

	indegree = malloc(sizeof(int) * H->nV);
	if (! indegree)
		FatalError( "Out of space!!!" );
	for (i = 0; i < H->nV; i ++)
		indegree[i] = H->TheLists[i]->V;

	topsort = malloc(sizeof(int) * H->nV);
	if (! topsort)
		FatalError("Out of space!!!");

	for (i = 0; i < H->nV; i ++)
		if (! indegree[i])
			PushList(i, L);

	printf("TopSort: ");
	for (i = 0; i < H->nV; i ++) {
		topsort[i] = PopList(L);
		if (topsort[i] == -1) {
			Error("Graph has a cycle");
			break;
		}
		printf("%d ", topsort[i]);

		P = H->TheLists[topsort[i]]->Next;
		while (P) {
			indegree[P->V] --;
			if (! indegree[P->V])
				PushList(P->V, L);
			P = P->Next;
		}
	}
	printf("\n");
}

main()
{
/*
	int edges[ ][2] = {
		1, 2, 1, 3, 1, 4,
		2, 4, 2, 5,
		3, 6,
		4, 3, 4, 6, 4, 7,
		5, 4, 5, 7,
		7, 6
	};	
*/
	int edges[ ][2] = {
		0, 1, 0, 2, 0, 3,
		1, 3, 1, 4,
		2, 5,
		3, 2, 3, 5, 3, 6,
		4, 3, 4, 6,
		6, 5
	};	
    GraPtr H;

	puts("     (0)------>(1)");
	puts("    /   \\     /   \\");
	puts("   V     V   V     V"); 
	puts("(2)<------(3)<------(4)");
	puts("   \\     /   \\     /");
	puts("    V   V     V   V");
	puts("     (5)<------(6)");
	printf("\n");

    H = InitializeGraph(edges, sizeof(edges) / sizeof(*edges));

//	PrintTable(H);

	TopSort(H);
}
