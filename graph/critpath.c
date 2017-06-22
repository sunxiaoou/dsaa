#include <stdio.h>
#include <stdlib.h>

#include "fatal.h"
#include "graph.h"


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

	while ((V = MaxUnknown(H)) != -1) {
		H->T[V].kdp.known = 1;
		P = frontLinkQ(H->T[V].Q);
		while (P) {
			E = P->data;
			d = H->T[V].kdp.distance + E->weight;
			if (H->T[E->adjacent].kdp.distance < d) {
				H->T[E->adjacent].kdp.distance = d;
				H->T[E->adjacent].kdp.path = V;
			}
			P = P->Next;
		}
	}

	return 0;
}


main()
{
	int edges[ ][3] = {
		0, 1, 3, 0, 2, 2,
		1, 3, 3, 1, 4, 2,
		2, 4, 2, 2, 5, 1,
		3, 6, 3,
		4, 6, 3, 4, 7, 2,
		5, 7, 2, 5, 8, 8,
		6, 9, 1,
		7, 9, 1,
		8, 9, 1
	};

	GraPtr H;

	H = InitializeGraph(edges, sizeof(edges) / sizeof(*edges));

	PrintGraph(H);

	Dijkstra(0, H);

	PrintKDP(H);
	printf("Critical Path is: ");
	PrintPath(9, H);
	printf("\n");
}
