#ifndef _PRTTREE_H
#define _PRTTREE_H

typedef struct TreeNode {
	struct TreeNode *Left;
	struct TreeNode *Right;
	void *X;
} TreeNode, *TreePtr;

// int (*pTNode)(void *);
char *(*pT2Str)(void *);
void *(*pNullNode)(void);
void DrawTree(TreePtr T, int depth);
void PrintTree(TreePtr T, int depth);

#endif  /* _PRTTREE_H */
