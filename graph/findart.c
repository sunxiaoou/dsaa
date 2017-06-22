#include <stdio.h>

#include "graph.h"

/* Reuse member in struct VertEnt */
#define Visited(x) G->T[x].kdp.known
#define Parent(x) G->T[x].kdp.distance
#define Num(x) G->T[x].indegree
#define Low(x) G->T[x].kdp.path

#define Min(x , y) (x < y ? x : y)


void FindArt(Vertex V, GraPtr G)
{
	static int Counter = 0;
	Position P;
	EdgePtr E;
	Vertex W;

	Visited(V) = 1;
	Num(V) = Low(V) = ++ Counter;
	P = frontLinkQ(G->T[V].Q);
	while(P) {
		E = P->data;
		W = E->adjacent;
		if (! Visited(W)) {	/* Forward edge */
			printf("%d ----- %d\n", V, W);
			Parent(W) = V;
			if (Num(V) == 1)	/* count childs of root */
				Parent(V) --;	/* initial value is -1 */
			FindArt(W, G);
			if ((Num(V) > 1 && Low(W) >= Num(V)) || (Num(V) == 1 && Parent(V) < -2))
				printf("%d is an articulaton point\n", V);
			Low(V) = Min(Low(V), Low(W)); 
		}
		else if (Parent(V) != W) {	/* Back edge */
			printf("%d - - - %d\n", V, W);
			Low(V) = Min(Low(V), Num(W));
		}
		P = P->Next;
	}
}

main()
{
	static int edges[][3] = {
		0, 1, 1, 0, 3, 1,
		1, 0, 1, 1, 2, 1,
		2, 1, 0, 2, 3, 1, 2, 6, 1,
		3, 0, 1, 3, 2, 1, 3, 4, 1, 3, 5, 1,
		4, 3, 1, 4, 5, 1,
		5, 3, 1, 5, 4, 1,
		6, 2, 1
	};
	GraPtr G;

	puts("(1)---------------(0)");
	puts(" |                 |");
	puts(" |                 |");
	puts("(2)---------------(3)");
	puts("   \\             /   \\");
	puts("    \\           /     \\");
	puts("     (6)     (4)-------(5)");
	printf("\n");

	G = InitializeGraph(edges, sizeof(edges) / sizeof(*edges));
//	PrintGraph(G);

	FindArt(0, G);
//	FindArt(2, G);
	PrintKDP(G);
}
