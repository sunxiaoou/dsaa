#include <stdio.h>
#include <stdlib.h>

#include "fatal.h"
#include "graph.h"

GraPtr InitializeGraph(int edges[][3], int num)
{
	int i;
	EdgePtr E;
	GraPtr G;

	G = malloc(sizeof(struct Graph));
	if( G == NULL )
		FatalError( "Out of space!!!" );

	G->nE = num;
	for (G->nV = 0, i = 0; i < G->nE; i ++) {
		G->nV = G->nV < edges[i][0] ? edges[i][0] : G->nV;
		G->nV = G->nV < edges[i][1] ? edges[i][1] : G->nV;
	}
	G->nV ++;

	G->T = malloc(sizeof(struct VertEnt) * G->nV);
	if( G->T == NULL )
		FatalError( "Out of space!!!" );

	for (i = 0; i < G->nV; i ++) {
		G->T[i].kdp.known = 0;
		G->T[i].kdp.distance = G->T[i].kdp.path = -1;
		G->T[i].indegree = 0;
		G->T[i].Q = CreateLinkQ();
	}

	for (i = 0; i < G->nE; i ++) {
		E = malloc(sizeof(Edge));
		E->adjacent = edges[i][1];
		E->weight = edges[i][2];
   		EnqLinkQ(E, G->T[edges[i][0]].Q);
		G->T[edges[i][1]].indegree ++;
	}

	return G;
}

Vertex MinUnknown(GraPtr G)
{
	int i, d;
	Vertex j;

	for (i = 0, j = d = -1; i < G->nV; i ++) {
		if (! G->T[i].kdp.known && G->T[i].kdp.distance != -1) {
			if (d == -1 || d > G->T[i].kdp.distance) {
				d = G->T[i].kdp.distance;
				j = i;
			}
		}
	}

	return j;
}

Vertex MaxUnknown(GraPtr G)
{
	int i, d;
	Vertex j;

	for (i = 0, j = d = -1; i < G->nV; i ++) {
		if (! G->T[i].kdp.known && G->T[i].kdp.distance != -1) {
			if (d == -1 || d < G->T[i].kdp.distance) {
				d = G->T[i].kdp.distance;
				j = i;
			}
		}
	}

	return j;
}

static void PrintList(List L)
{
	int i;
	Position P;
	EdgePtr E;

	P = L;
	for (i = 0; P->Next; i ++) {
		P = P->Next;
		E = P->data;
		printf("%d,%d ", E->adjacent, E->weight);
	}
	printf("\n");
}

void PrintGraph(GraPtr G)
{
	int i;

	for (i = 0; i < G->nV; i ++) {
		printf("%02d: %di ", i, G->T[i].indegree);
		PrintList(headLinkQ(G->T[i].Q));
	}
}

void PrintKDP(GraPtr G)
{
	int i;

	for (i = 0; i < G->nV; i ++)
		printf("%02d: %d %d %d\n", i, G->T[i].kdp.known,
		   	G->T[i].kdp.distance, G->T[i].kdp.path);
}

void PrintPath(Vertex V, GraPtr G)
{
	if (G->T[V].kdp.path >= 0) {
		PrintPath(G->T[V].kdp.path, G);
		printf(" to ");
	}
	printf("%d", V);
}

#if MYTEST
main()
{
	int edges[ ][3] = {
		0, 1, 2, 0, 3, 1,
		1, 3, 3, 1, 4, 10,
		2, 0, 4, 2, 5, 5,
		3, 2, 2, 3, 4, 2, 3, 5, 8, 3, 6, 4,
		4, 6, 6,
		6, 5, 1
	};	
	GraPtr G;

	puts("     (0)---2-->(1)");
	puts("   4^   \\1   3/   \\10");
	puts("   /     V   V     V"); 
	puts("(2)<--2---(3)---2-->(4)");
	puts("   \\5   8/   \\4   6/");
	puts("    V   V     V   V");
	puts("     (5)<--1---(6)");
	printf("\n");

	G = InitializeGraph(edges, sizeof(edges) / sizeof(*edges));

	PrintGraph(G);
	PrintKDP(G);
}
#endif
