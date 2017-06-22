#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "linkque.h"

typedef int Vertex;

typedef struct Edge {
	int weight;
	Vertex adjacent;
} Edge, *EdgePtr;

struct KDP {
	int known;
	int distance;
	Vertex path;
};

struct VertEnt {
	int indegree;
	struct KDP kdp;
	LinkQPtr Q;
};

typedef struct Graph {
	int nV;
	int nE;
	struct VertEnt *T;
} Graph, *GraPtr;

GraPtr InitializeGraph(int edges[][3], int num);
Vertex MinUnknown(GraPtr G);
Vertex MaxUnknown(GraPtr G);
void PrintGraph(GraPtr G);
void PrintKDP(GraPtr G);
void PrintPath(Vertex V, GraPtr G);

#endif /* _GRAPH_H_ */
