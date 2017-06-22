#include <stdio.h>

#include "disjsets.h"
#include "binheap.h"

typedef struct Edge {
	int U;
	int V;
	int weight;
} Edge, *EdgePtr;


int valueOfElement(ElementType e)
{
	return ((EdgePtr)e)->weight;
}

int compareElement(ElementType a, ElementType b)
{
	if (! a || ! b)
		return 0;

	return ((EdgePtr)a)->weight - ((EdgePtr)b)->weight;
}

void Kruskal(Edge *edges, int num)
{
	int i, nV, EdgesAccepted;
	DisjSet S;
	PriorityQueue H;
	int U, V;
	SetType Uset, Vset;
	EdgePtr E;

	Initialize(S);
	H = CreateHeap(100);
	H->pValue = valueOfElement;
	H->pCompare = compareElement;

	BuildHeap(edges, sizeof(Edge), num, H);

	for (nV = 0, i = 0; i < num; i ++) {
		nV = nV < edges[i].U ? edges[i].U : nV;
		nV = nV < edges[i].V ? edges[i].V : nV;
	}

	PrintDisjSet(nV + 1, S);
	EdgesAccepted = 0;
	while (EdgesAccepted < nV - 1) {
		E = DeleteHeap(H);
		Uset = Find(E->U, S);
		Vset = Find(E->V, S);
		if (Uset != Vset) {
			EdgesAccepted ++;
			SetUnion(S, Uset, Vset);
			printf("Add Edge: %d %d %d\n", E->U, E->V, E->weight);
		}
	}
	PrintDisjSet(nV + 1, S);
}

main()
{
	static Edge edges[] = {
		1, 2, 2, 1, 4, 1,
		2, 4, 3, 2, 5, 10,
		3, 1, 4, 3, 6, 5,
		4, 3, 2, 4, 5, 7, 4, 6, 8, 4, 7, 4,
		5, 7, 6,
		7, 6, 1
	};

	puts("     (1)---2---(2)");
	puts("   4/   \\1   3/   \\10");
	puts("   /     \\   /     \\"); 
	puts("(3)---2---(4)---7---(5)");
	puts("   \\5   8/   \\4   6/");
	puts("    \\   /     \\   /");
	puts("     (6)---1---(7)");
	printf("\n");

	puts("     (1)---2---(2)");
	puts("        \\1");
	puts("         \\"); 
	puts("(3)---2---(4)       (5)");
	puts("             \\4   6/");
	puts("              \\   /");
	puts("     (6)---1---(7)");
	printf("\n");

	Kruskal(edges, sizeof(edges) / sizeof(*edges));
}
