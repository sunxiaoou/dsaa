#include <stdlib.h>

#include "redblack.h"
#include "fatal.h"

// #include "prttree.h"


/* START: fig12_14.txt */
#if 0
        typedef enum ColorType { Red, Black } ColorType;

        struct RedBlackNode
        {
            RedBlackTree Left;
            RedBlackTree Right;
            ElementType  Element;
            ColorType    Color;
        };

        static Position NullNode = NULL;  /* Needs initialization */
#endif

static Position Root;

        /* Initialization procedure */
        RedBlackTree
        Initialize( void )
        {
            RedBlackTree T;

            if( NullNode == NULL )
            {
                NullNode = malloc( sizeof( struct RedBlackNode ) );
                if( NullNode == NULL )
                    FatalError( "Out of space!!!" );
                NullNode->Left = NullNode->Right = NullNode;
                NullNode->Color = Black;
                NullNode->Element = 12345;
            }

            /* Create the header node */
            T = malloc( sizeof( struct RedBlackNode ) );
            if( T == NULL )
                FatalError( "Out of space!!!" );
            T->Element = NegInfinity;
            T->Left = T->Right = NullNode;
            T->Color = Black;

Root = T;

            return T;
        }
/* END */

        void
        Output( ElementType Element )
        {
            printf( "%d\n", Element );
        }

#if 0
/* START: fig12_13.txt */
        /* Print the tree, watch out for NullNode, */
        /* and skip header */

        static void
        DoPrint( RedBlackTree T )
        {
            if( T != NullNode )
            {
                DoPrint( T->Left );
                Output( T->Element );
                DoPrint( T->Right );
            }
        }

        void
        PrintTree( RedBlackTree T )
        {
            DoPrint( T->Right );
        }
/* END */
#endif

        static RedBlackTree
        MakeEmptyRec( RedBlackTree T )
        {
            if( T != NullNode )
            {
                MakeEmptyRec( T->Left );
                MakeEmptyRec( T->Right );
                free( T );
            }
            return NullNode;
        }

        RedBlackTree
        MakeEmpty( RedBlackTree T )
        {
            T->Right = MakeEmptyRec( T->Right );
            return T;
        }

        Position
        Find( ElementType X, RedBlackTree T )
        {
            if( T == NullNode )
                return NullNode;
            if( X < T->Element )
                return Find( X, T->Left );
            else
            if( X > T->Element )
                return Find( X, T->Right );
            else
                return T;
        }

        Position
        FindMin( RedBlackTree T )
        {
            T = T->Right;
            while( T->Left != NullNode )
                T = T->Left;

            return T;
        }

        Position
        FindMax( RedBlackTree T )
        {
            while( T->Right != NullNode )
                T = T->Right;

            return T;
        }

        /* This function can be called only if K2 has a left child */
        /* Perform a rotate between a node (K2) and its left child */
        /* Update heights, then return new root */

        static Position
        LeftSingleRotate( Position K2 )
        {
            Position K1;

            K1 = K2->Left;
            K2->Left = K1->Right;
            K1->Right = K2;

            return K1;  /* New root */
        }

        /* This function can be called only if K1 has a right child */
        /* Perform a rotate between a node (K1) and its right child */
        /* Update heights, then return new root */

        static Position
        RightSingleRotate( Position K1 )
        {
            Position K2;

            K2 = K1->Right;
            K1->Right = K2->Left;
            K2->Left = K1;

            return K2;  /* New root */
        }

/* START: fig12_15.txt */
        /* Perform a rotation at node X */
        /* (whose parent is passed as a parameter) */
        /* The child is deduced by examining Item */

        static Position
        Rotate( ElementType Item, Position Parent )
        {

            if( Item < Parent->Element )
                return Parent->Left = Item < Parent->Left->Element ?
                    LeftSingleRotate( Parent->Left ) :
                    RightSingleRotate( Parent->Left );
            else
                return Parent->Right = Item < Parent->Right->Element ?
                    LeftSingleRotate( Parent->Right ) :
                    RightSingleRotate( Parent->Right );
        }
/* END */

/* START: fig12_16.txt */

        static
        void HandleReorient( ElementType Item, RedBlackTree T )
        {
            X->Color = Red;        /* Do the color flip */
            X->Left->Color = Black;
            X->Right->Color = Black;

            if( P->Color == Red )  /* Have to rotate */
            {
                GP->Color = Red;
                if( (Item < GP->Element) != (Item < P->Element) )
                    P = Rotate( Item, GP );  /* Start double rotate */
                X = Rotate( Item, GGP );
                X->Color = Black;
            }
            T->Right->Color = Black;  /* Make root black */
        }

        RedBlackTree
        Insert( ElementType Item, RedBlackTree T )
        {
            X = P = GP = T;
            NullNode->Element = Item;
            while( X->Element != Item )  /* Descend down the tree */
            {
                GGP = GP; GP = P; P = X;
                if( Item < X->Element )
                    X = X->Left;
                else
                    X = X->Right;
                if( X->Left->Color == Red && X->Right->Color == Red )
                    HandleReorient( Item, T );
            }

            if( X != NullNode )
                return NullNode;  /* Duplicate */

            X = malloc( sizeof( struct RedBlackNode ) );
            if( X == NULL )
                FatalError( "Out of space!!!" );
            X->Element = Item;
            X->Left = X->Right = NullNode;

            if( Item < P->Element )  /* Attach to its parent */
                P->Left = X;
            else
                P->Right = X;
            HandleReorient( Item, T ); /* Color it red; maybe rotate */

            return T;
        }
/* END */

static ElementType findMin(RedBlackTree T)
{
    while( T->Left != NullNode )
        T = T->Left;

    return T->Element;
}

static ElementType findMax(RedBlackTree T)
{
    while(T->Right != NullNode)
        T = T->Right;

    return T->Element;
}

static Position P2Red(Position GP, Position P, Position X, Position B)
{
	P->Color = Red;
	B->Color = Black;

	if(P->Right == B) {
		if(GP->Left == P)
			GP->Left = RightSingleRotate(P);
		else
			GP->Right = RightSingleRotate(P);

		return P->Right;
	}
	else {
		if(GP->Left == P)
			GP->Left = LeftSingleRotate(P);
		else
			GP->Right = LeftSingleRotate(P);

		return P->Left;
	}
}

static void X2Red(Position GP, Position P, Position X, Position B)
{
	P->Color = Black;
	X->Color = Red;

	if (B->Left->Color == Black && B->Right->Color == Black) {
		if(B != NullNode)
			B->Color = Red;
		return;
	}
	
	if (P->Right == B) {
		if (B->Left->Color == Red) {
			P->Right = LeftSingleRotate(B);
			if(GP->Right == P)
				GP->Right = RightSingleRotate(P);
			else
				GP->Left = RightSingleRotate(P);
		}
		else {
			B->Color = Red;
			B->Right->Color = Black;
			if(GP->Right == P)
				GP->Right = RightSingleRotate(P);
			else
				GP->Left = RightSingleRotate(P);
		}
	}
	else {
		if (B->Right->Color == Red) {
			P->Left = RightSingleRotate(B);
			if(GP->Left == P)
				GP->Left = LeftSingleRotate(P);
			else
				GP->Right = LeftSingleRotate(P);
		}
		else {
			B->Color = Red;
			B->Left->Color = Black;
			if(GP->Right == P)
				GP->Right = LeftSingleRotate(P);
			else
				GP->Left = LeftSingleRotate(P);
		}
	}
}

static ElementType Delete(ElementType Item, Position GP, Position P, Position X)
{
	Position B;

//	printf("Delete(I=%d GP=%d P=%d X=%d)\n", Item, GP->Element, P->Element, X->Element);
	if (X == NullNode)
		return -1;

	B = (X == P->Left) ? P->Right : P->Left;

	if (P->Color == Black && X->Color == Black && B->Color == Red) {
//		printf("P2Red(GP=%d P=%d X=%d B=%d)\n", GP->Element, P->Element, X->Element, B->Element);
		B = P2Red(GP, P, X, B);
//		DrawTree((TreePtr)(Root->Right), 0);
	}

	if (X->Color == Black && X->Left->Color == Black && X->Right->Color == Black) {
//		printf("X2Red(GP=%d P=%d X=%d B=%d)\n", GP->Element, P->Element, X->Element, B->Element);
		X2Red(GP, P, X, B);
//		DrawTree((TreePtr)(Root->Right), 0);
	}

	if (Item < X->Element)
		Item = Delete(Item, P, X, X->Left);
	else if (Item > X->Element)
		Item = Delete(Item, P, X, X->Right);
	else if (X->Right != NullNode) {
		Item = findMin(X->Right);
		X->Element = Item;
		Item = Delete(Item, P, X, X->Right);
	}
	else if (X->Left != NullNode) {
		Item = findMax(X->Left);
		X->Element = Item;
		Item = Delete(Item, P, X, X->Left);
	}
	else {
		if(P->Right == X)
			P->Right = NullNode;
		else
			P->Left = NullNode;
		free(X);
		X = NullNode;
	}

	return Item;
}

ElementType Remove(ElementType Item, RedBlackTree T)
{
	T->Color = Red;
	Delete(Item, T, T, T->Right);
	T->Color = T->Right->Color = Black;
}

ElementType Retrieve(Position P)
{
	return P->Element;
}


int Check(Position P, Position X)
{
	int leftHeight, rightHeight, add;

	if (P->Element == NegInfinity && X->Color != Black)
		return -1;

	if (P->Color == Red && X->Color == Red)
		return -1;

	if (X == NullNode)
		return 0; 

	if ((leftHeight = Check(X, X->Left)) == -1)
		printf("%d error\n", X->Left->Element);
	if ((rightHeight = Check(X, X->Right)) == -1)
		printf("%d error\n", X->Right->Element);

	if (leftHeight != rightHeight)
		printf("%d(%d)%d(%d) error\n", X->Left->Element, leftHeight,
			X->Right->Element, rightHeight);


	add = X->Color == Black ? 1 : 0;

/*
	The current subtree is not a red black tree if and only if
	one or more of current node's children is a root of an invalid tree
	or they contain different number of black nodes on a path to a null node.
*/


	if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight)
		return -1; 

	return leftHeight + add;
}


char *Node2Str(void *T)
{
	static char s[8];
	Position X;

	X = (Position)T;
	if (X->Color == Black)
		sprintf(s, "%02db", X->Element);
	else
		sprintf(s, "%02dr", X->Element);

	return s;
}

void *GetNullNode(void)
{
	return NullNode;
}
