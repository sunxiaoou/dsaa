#include <stdio.h>
#include <stdlib.h>

#include "fatal.h"

typedef int Vertex;

typedef struct ListNode {
    Vertex V;
    struct ListNode *Next;
} ListNode, *Position, *List;

typedef struct LinkQue {
	List head;	/* front is always head->next */
	Position rear;
	int size;
} LinkQue, *LinkQPtr;

typedef struct VertEnt {
	int known;
	int dist;
	Vertex path;
	LinkQPtr Q;
} VertEnt;

typedef struct Graph {
	int nV;
	int nE;
	VertEnt *table;
} Graph, *GraPtr;


LinkQPtr CreateLinkQ(void)
{
	LinkQPtr ll;

	ll = malloc(sizeof(LinkQue));
	if (! ll) {
		printf("malloc failed\n");
		return NULL;
	}

	ll->head = malloc(sizeof(ListNode));
	if (! ll->head) {
		printf("malloc failed\n");
		return NULL;
	}

	ll->head->Next = NULL;
	ll->rear = ll->head;
	ll->size = 0;

	return ll;
}

int IsEmptyLinkQ(LinkQPtr Q)
{
	return Q->head->Next == NULL;
}

Position frontLinkQ(LinkQPtr Q)
{
	return Q->head->Next;
}

int EnqLinkQ(Vertex V, LinkQPtr Q)
{
	Position P;

	P = malloc(sizeof(struct ListNode));
	if(! P)
		return -1;

	P->V = V;
	P->Next = NULL;

	Q->rear->Next = P;
	Q->rear = P;

	Q->size ++;

	return 0;
}

Vertex DeqLinkQ(LinkQPtr Q)
{
	Vertex V;	
	Position P;

	if (IsEmptyLinkQ(Q))
		return -1;

	P = Q->head->Next;
	V = P->V;
	Q->head->Next = P->Next;
	free(P);

	if (IsEmptyLinkQ(Q))
		Q->rear = Q->head;
	Q->size --;

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

	H->table = malloc(sizeof(VertEnt) * H->nV );
	if( H->table == NULL )
		FatalError( "Out of space!!!" );

	for (i = 0; i < H->nV; i ++) {
		H->table[i].known = 0;
		H->table[i].dist = H->table[i].path = -1;
		H->table[i].Q = CreateLinkQ();
	}

	for (i = 0; i < H->nE; i ++)
   		EnqLinkQ(edges[i][1], H->table[edges[i][0]].Q);

	return H;
}

void PrintList(List L)
{
	int i;
	Position p;

	p = L;
	for (i = 0; p->Next; i ++) {
		p = p->Next;
		printf("%d ", p->V);
	}
	printf("\n");
}

void PrintGraph(GraPtr H)
{
	int i;

	for (i = 0; i < H->nV; i ++) {
		printf("%02d: ", i);
		PrintList(H->table[i].Q->head);	
	}
}

void PrintGra2(GraPtr H)
{
	int i;

	for (i = 0; i < H->nV; i ++)
		printf("%d: %d %d %d\n", i, H->table[i].known, H->table[i].dist,
		   	H->table[i].path);
}

int unweighted(Vertex V, GraPtr H)
{
	int i;
	Position P;
	LinkQPtr Q;

	if (V >= H->nV) {
		printf("out of range\n");		
		return -1;
	}
	H->table[V].dist = H->table[V].path = 0;
	PrintGra2(H);

	Q = CreateLinkQ();

	EnqLinkQ(V, Q);

	while((V = DeqLinkQ(Q)) != -1) {
		H->table[V].known = 1;
		P = frontLinkQ(H->table[V].Q);
		printf("deq(%d)enq(", V);
		while (P) {
			if(H->table[P->V].dist == -1) {
				H->table[P->V].dist = H->table[V].dist + 1;
				H->table[P->V].path = V;
				EnqLinkQ(P->V, Q);
				printf("%d ", P->V);
			}
			P = P->Next;
		}
		printf(")\n");
		PrintGra2(H);
	}

	return 0;
}

main()
{
/*
	int edges[ ][2] = {
		1, 2, 1, 4,
		2, 4, 2, 5,
		3, 1, 3, 6,
		4, 3, 4, 5, 4, 6, 4, 7,
		5, 7,
		7, 6	
	};	
*/
	Vertex edges[ ][2] = {
		0, 1, 0, 3,
		1, 3, 1, 4,
		2, 0, 2, 5,
		3, 2, 3, 4, 3, 5, 3, 6,
		4, 6,
		6, 5	
	};	
	GraPtr H;

	puts("     (0)------>(1)");
	puts("    A   \\     /   \\");
	puts("   /     V   V     V"); 
	puts("(2)<------(3)------>(4)");
	puts("   \\     /   \\     /");
	puts("    V   V     V   V");
	puts("     (5)<------(6)");
	printf("\n");

	H = InitializeGraph(edges, sizeof(edges) / sizeof(*edges));

	PrintGraph(H);

	unweighted(2, H);
}
