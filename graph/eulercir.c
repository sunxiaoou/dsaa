#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#define Min(x , y) (x < y ? x : y)

#define Q(x) G->T[x].Q
#define P(x) G->T[x].Q->rear
/* Reuse member in struct VertEnt */
#define Visited(x) G->T[x].kdp.known
#define Parent(x) G->T[x].kdp.distance
#define Degree(x) G->T[x].indegree

void setRears(GraPtr G)
{
	int i;

	for (i = 0; i < G->nV; i ++)
		P(i) = frontLinkQ(Q(i));
}

int valueOfVtx(void *v)
{
	return *((Vertex *)v);
}

int compareVtx(void *a, void *b)
{
	if (! a || ! b)
		return -1;

	return *(Vertex *)a - *(Vertex *)b;
}

Vertex searchVtx(LinkQPtr Q, GraPtr G) 
{
	Vertex V;
	Position P;

	P = headLinkQ(Q);
	while (P = advanceLinkQ(P)) {
		V = *(Vertex *)retrieveLinkQ(P);
		if (Degree(V))
			return V;
	}

	return -1;
}

Position insertVtx(Vertex V, Position P, LinkQPtr Q)
{
	Vertex *X;

	X = malloc(sizeof(Vertex));
	*X = V;

	return InsertLinkQ(X, P, Q);
}

int setAdjacent(Vertex V, LinkQPtr Q)
{
	Position P;
	EdgePtr E;

	P = headLinkQ(Q);
	while (P = advanceLinkQ(P)) {
		E = retrieveLinkQ(P);
		if (E->adjacent == V) {
			E->weight = 0;
			return 0;
		}
	}

	return -1;
}

Position DFS(Vertex V, GraPtr G, Position P, LinkQPtr Q)
{
	Vertex W;
	EdgePtr E;

	if (Parent(V) != -1)
		setAdjacent(Parent(V), Q(V));

	while (P(V)) {
		E = retrieveLinkQ(P(V));
		W = E->adjacent;
		P(V) = advanceLinkQ(P(V));
		if (E->weight) {
/*
			printf("%d ----- %d\n", V, W);
*/
			P = insertVtx(W, P, Q);
			Parent(W) = V;
			Degree(W) --;
			Degree(V) --;
			P = DFS(W, G, P, Q);

			return P;
		}
	}

	return P;
}

int Eulercir(Vertex V, GraPtr G)
{
	int rc = 0;
	Position P;
	LinkQPtr Q;

	if (V >= G->nV) {
		printf("%d is out of range\n", V);
		return -1;	
	}

	setRears(G);

	Q = CreateLinkQ();
	Q->pValue = valueOfVtx;
	Q->pCompare = compareVtx;

	do {
		P = FindLinkQ(&V, Q);
		if (! P)
			P = insertVtx(V, headLinkQ(Q), Q);
		P = DFS(V, G, P, Q);
		if (V != *(Vertex *)retrieveLinkQ(P)) {
			printf("%d to %d is not an Euler circuit\n", 			
				V, *(Vertex *)retrieveLinkQ(P));
			rc = -1;
		}
	} while ((V = searchVtx(Q, G)) != -1);
		
	PrintLinkQ(Q);

	return rc;
}


int main(int argc, char *argv[])
{
/*
	static int edges[][3] = {
		0, 1, 1, 0, 3, 1,
		1, 0, 1, 1, 2, 1,
		2, 1, 0, 2, 3, 1, 2, 6, 1,
		3, 0, 1, 3, 2, 1, 3, 4, 1, 3, 5, 1,
		4, 3, 1, 4, 5, 1,
		5, 3, 1, 5, 4, 1,
		6, 2, 1
	};
*/

	static int edges[][3] = {
		0, 2, 1, 0, 3, 1,
		1, 2, 1, 1, 7, 1,
		2, 0, 1, 2, 1, 1, 2, 3, 1, 2, 5, 1, 2, 6, 1, 2, 8, 1,
		3, 0, 1, 3, 2, 1, 3, 4, 1, 3, 6, 1, 3, 9, 1, 3, 10, 1,
		4, 3, 1, 4, 9, 1,
		5, 2, 1, 5, 8, 1,
		6, 2, 1, 6, 3, 1, 6, 8, 1, 6, 9, 1,
		7, 1, 1, 7, 8, 1,
		8, 2, 1, 8, 5, 1, 8, 6, 1, 8, 7, 1, 8, 9, 1, 8, 11, 1,
		9, 3, 1, 9, 4, 1, 9, 6, 1, 9, 8, 1, 9, 10, 1, 9, 11, 1,
		10, 3, 1, 10, 9, 1,
		11, 8, 1, 11, 9, 1
	};

	GraPtr G;

	if (argc < 2) {
/*
		puts("(1)---------------(0)");
		puts(" |                 |");
		puts(" |                 |");
		puts("(2)---------------(3)");
		puts("   \\             /   \\");
		puts("    \\           /     \\");
		puts("     (6)     (4)-------(5)");
*/
		puts("Euler Circuit");
		puts("               (0)");
		puts("              /   \\");
		puts("             /     \\");
		puts("(1)-------(2)-------(3)-------(4)");
		puts(" |       / | \\     /|  \\     /");
		puts(" |      /  |  \\   / |   \\   /");
		puts(" |   (5)   |   (6)  |     |");
		puts(" |      \\  |  /   \\ |   /   \\");
		puts(" |       \\ | /     \\|  /     \\");
		puts("(7)-------(8)-------(9)------(10)");
		puts("             \\     /");
		puts("              \\   /");
		puts("              (11)");
		printf("\n");

		printf("%s Vertex(0 - 11)\n", argv[0]);
		exit(1);
	}

	G = InitializeGraph(edges, sizeof(edges) / sizeof(*edges));
//	PrintGraph(G);

	Eulercir(atoi(argv[1]), G);
}
