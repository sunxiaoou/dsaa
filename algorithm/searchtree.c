#include <stdlib.h>
#include "searchtree.h"
#include "fatal.h"

SearchTree MakeEmpty( SearchTree T )
{
	if( T != NULL )
	{
		MakeEmpty( T->Left );
		MakeEmpty( T->Right );
		free( T );
	}
	return NULL;
}

Position Find( ElementType X, SearchTree T )
{
	if( T == NULL )
		return NULL;
	if( X < T->Element )
		return Find( X, T->Left );
	else
	if( X > T->Element )
		return Find( X, T->Right );
	else
		return T;
}

Position FindMin( SearchTree T )
{
	if( T == NULL )
		return NULL;
	else
	if( T->Left == NULL )
		return T;
	else
		return FindMin( T->Left );
}

Position FindMax( SearchTree T )
{
	if( T != NULL )
		while( T->Right != NULL )
			T = T->Right;

	return T;
}

SearchTree Insert( ElementType X, SearchTree T )
{
	if( T == NULL )
	{
		/* Create and return a one-node tree */
		T = malloc( sizeof( struct SearchNode ) );
		if( T == NULL )
			FatalError( "Out of space!!!" );
		else
		{
			T->Element = X;
			T->Frequency = 1;
			T->Left = T->Right = NULL;
		}
	}
	else
	if( X < T->Element )
		T->Left = Insert( X, T->Left );
	else
	if( X > T->Element )
		T->Right = Insert( X, T->Right );
	/* Else X is in the tree already; we'll do nothing */
	else
		T->Frequency ++;

	return T;  /* Do not forget this line!! */
}

SearchTree Delete( ElementType X, SearchTree T )
{
	Position TmpCell;

	if( T == NULL )
		Error( "Element not found" );
	else
	if( X < T->Element )  /* Go left */
		T->Left = Delete( X, T->Left );
	else
	if( X > T->Element )  /* Go right */
		T->Right = Delete( X, T->Right );
	else  /* Found element to be deleted */
	if (T->Frequency > 1)
		T->Frequency --;
	else
	if( T->Left && T->Right )  /* Two children */
	{
		/* Replace with smallest in right subtree */
		TmpCell = FindMin( T->Right );
		T->Element = TmpCell->Element;
		T->Right = Delete( T->Element, T->Right );
	}
	else  /* One or zero children */
	{
		TmpCell = T;
		if( T->Left == NULL ) /* Also handles 0 children */
			T = T->Right;
		else if( T->Right == NULL )
			T = T->Left;
		free( TmpCell );
	}

	return T;
}

ElementType Retrieve( Position P )
{
	return P->Element;
}

int STElement(void *T)
{
	return ((SearchTree)T)->Element;
}

int STFrequency(void *T)
{
	return ((SearchTree)T)->Frequency;
}

char *ST2Str(void *T)
{
	static char s[80];
	int i;

	sprintf(s, "%d ", ((SearchTree)T)->Element);
	for (i = 1; i < ((SearchTree)T)->Frequency; i ++)
		sprintf(s, "%s%d ", s, ((SearchTree)T)->Element);

	return s;
}
