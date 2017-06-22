#include <stdio.h>
#include <stdlib.h>

#include "fatal.h"
#include "graph.h"

int sumCosts(GraPtr H)
{
	int i, sum;

	for (i = 0, sum = 0; i < H->nV; i ++)
		sum += H->T[i].kdp.distance;

	return sum;
}

int Dijkstra(Vertex V, GraPtr H)
{
	int d;
	EdgePtr E;
	Position P;

	if (V < 0 || V >= H->nV) {
		printf("out of range\n");
		return -1;
	}
	H->T[V].kdp.distance = 0;
	PrintKDP(H);

	while ((V = MinUnknown(H)) != -1) {
		H->T[V].kdp.known = 1;
		P = frontLinkQ(H->T[V].Q);
		printf("del(%d)ins(", V);
		while (P) {
			E = P->data;
//			d = H->T[V].kdp.distance + E->weight;
			d = E->weight;
			if (! H->T[E->adjacent].kdp.known && 
				(H->T[E->adjacent].kdp.distance == -1 ||
				d < H->T[E->adjacent].kdp.distance))
		   	{
				H->T[E->adjacent].kdp.distance = d;
				H->T[E->adjacent].kdp.path = V;
				printf("%d ", E->adjacent);
			}
			P = P->Next;
		}
		printf(")\n");
		PrintKDP(H);
		PrintPath(V, H);
		printf("\n");
	}

	return 0;
}


main()
{
	int edges[ ][3] = {
		0, 1, 2, 0, 2, 4, 0, 3, 1,
		1, 0, 2, 1, 3, 3, 1, 4, 10,
		2, 0, 4, 2, 3, 2, 2, 5, 5,
		3, 0, 1, 3, 1, 3, 3, 2, 2, 3, 4, 7, 3, 5, 8, 3, 6, 4,
		4, 1, 10, 4, 3, 7, 4, 6, 6,
		5, 2, 5, 5, 3, 8, 5, 6, 1,
		6, 3, 4, 6, 4, 6, 6, 5, 1
	};	
	GraPtr H;

	puts("     (0)---2---(1)");
	puts("   4/   \\1   3/   \\10");
	puts("   /     \\   /     \\"); 
	puts("(2)---2---(3)---7---(4)");
	puts("   \\5   8/   \\4   6/");
	puts("    \\   /     \\   /");
	puts("     (5)---1---(6)");
	printf("\n");

	H = InitializeGraph(edges, sizeof(edges) / sizeof(*edges));

	PrintGraph(H);

	Dijkstra(4, H);

	printf("Minimum spanning tree costs is %d.\n", sumCosts(H));
}
