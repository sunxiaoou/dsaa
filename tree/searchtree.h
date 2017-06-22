#ifndef _SEARCHTREE_H
#define _SEARCHTREE_H

typedef int ElementType;

typedef struct SearchNode
{
	struct SearchNode *Left;
	struct SearchNode *Right;
	ElementType Element;
	int Frequency;
	int Height;
} SearchNode, *Position, *SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
ElementType Retrieve(Position P);

/* for generic tree print */
char *Node2Str(void *T);
char *ST2Str(void *T);


#endif  /* _SEARCHTREE_H */
