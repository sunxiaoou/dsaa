#ifndef _REDBLACK_H
#define _REDBLACK_H

#include <stdlib.h>

#include "fatal.h"

typedef int ElementType;

struct RedBlackNode;
typedef struct RedBlackNode *Position;
typedef struct RedBlackNode *RedBlackTree;

typedef enum ColorType { Red, Black } ColorType;

struct RedBlackNode
{
    RedBlackTree Left;
    RedBlackTree Right;
    ElementType  Element;
    ColorType    Color;
};

RedBlackTree MakeEmpty(RedBlackTree T);
Position Find(ElementType Item, RedBlackTree T);
Position FindMin(RedBlackTree T);
Position FindMax(RedBlackTree T);
RedBlackTree Initialize(void);
RedBlackTree Insert(ElementType Item, RedBlackTree T);
ElementType Remove(ElementType Item, RedBlackTree T);
ElementType Retrieve(Position P);
int Check(Position P, Position X);
// void PrintTree( RedBlackTree T );

char *Node2Str(void *T);
void *GetNullNode(void);

#define NegInfinity (-10000)

static Position NullNode = NULL;  /* Needs initialization */
static Position X, B, P, GP, GGP;

#endif  /* _REDBLACK_H */
