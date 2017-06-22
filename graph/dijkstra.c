#include <stdio.h>
#include <stdlib.h>

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
//	PrintKDP(H);

	while ((V = MinUnknown(H)) != -1) {
		H->T[V].kdp.known = 1;
		P = frontLinkQ(H->T[V].Q);
//		printf("del(%d)ins(", V);
		while (P) {
			E = P->data;
			d = H->T[V].kdp.distance + E->weight;
			if (H->T[E->adjacent].kdp.distance == -1 ||
				d < H->T[E->adjacent].kdp.distance)
		   	{
				H->T[E->adjacent].kdp.distance = d;
				H->T[E->adjacent].kdp.path = V;
//				printf("%d ", E->adjacent);
			}
			P = P->Next;
		}
//		printf(")\n");
//		PrintKDP(H);
		PrintPath(V, H);
		printf("\n");
	}

	return 0;
}


int main(int argc, char *argv[])
{
	int edges[ ][3] = {
		0, 1, 2, 0, 3, 1,
		1, 3, 3, 1, 4, 10,
		2, 0, 4, 2, 5, 5,
		3, 2, 2, 3, 4, 2, 3, 5, 8, 3, 6, 4,
		4, 6, 6,
		6, 5, 1
	};	
	GraPtr H;

	if (argc < 2) {
		puts("     (0)---2-->(1)");
		puts("   4^   \\1   3/   \\10");
		puts("   /     V   V     V"); 
		puts("(2)<--2---(3)---2-->(4)");
		puts("   \\5   8/   \\4   6/");
		puts("    V   V     V   V");
		puts("     (5)<--1---(6)");
		printf("\n");

		printf("%s Vertex(0 - 7)\n", argv[0]);
		exit(1);
	}

	H = InitializeGraph(edges, sizeof(edges) / sizeof(*edges));

//	PrintGraph(H);

	Dijkstra(atoi(argv[1]), H);
}
