#include <stdio.h>

#include "graph.h"

void Dfs(Vertex V, GraPtr G)
{
	Position P;
	EdgePtr E;

	G->T[V].kdp.known = 1;
	P = frontLinkQ(G->T[V].Q);
	while(P) {
		E = P->data;
		if (! G->T[E->adjacent].kdp.known) {
			printf("%d ----- %d\n", V, E->adjacent); 
			Dfs(E->adjacent, G);
		}

		P = P->Next;
	}
}

main() {
	static int edges[][3] = {
		0, 1, 1, 0, 3, 1, 0, 4, 1,
		1, 0, 1, 1, 2, 1, 1, 3, 1,
		2, 1, 1, 2, 3, 1, 2, 4, 1,
		3, 0, 1, 3, 1, 1, 3, 2, 1,
		4, 0, 1, 4, 2, 1
	};
	GraPtr G;

	G = InitializeGraph(edges, sizeof(edges) / sizeof(*edges));
	PrintGraph(G);
	PrintKDP(G);

	Dfs(0, G);
}
