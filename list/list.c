        #include "list.h"
        #include <stdlib.h>
        #include "fatal.h"

        /* Place in the interface file */
        struct Node
        {
            ElementType Element;
            Position    Next;
        };

        List
        MakeEmpty( List L )
        {
            if( L != NULL )
                DeleteList( L );
            L = malloc( sizeof( struct Node ) );
            if( L == NULL )
                FatalError( "Out of memory!" );
            L->Next = NULL;
            return L;
        }

/* START: fig3_8.txt */
        /* Return true if L is empty */

        int
        IsEmpty( List L )
        {
            return L->Next == NULL;
        }
/* END */

/* START: fig3_9.txt */
        /* Return true if P is the last position in list L */
        /* Parameter L is unused in this implementation */

        int IsLast( Position P, List L )
        {
            return P->Next == NULL;
        }
/* END */

/* START: fig3_10.txt */
        /* Return Position of X in L; NULL if not found */

        Position
        Find( ElementType X, List L )
        {
            Position P;

/* 1*/      P = L->Next;
/* 2*/      while( P != NULL && P->Element != X )
/* 3*/          P = P->Next;

/* 4*/      return P;
        }
/* END */

/* START: fig3_11.txt */
        /* Delete from a list */
        /* Cell pointed to by P->Next is wiped out */
        /* Assume that the position is legal */
        /* Assume use of a header node */

        void
        Delete( ElementType X, List L )
        {
            Position P, TmpCell;

            P = FindPrevious( X, L );

            if( !IsLast( P, L ) )  /* Assumption of header use */
            {                      /* X is found; delete it */
                TmpCell = P->Next;
                P->Next = TmpCell->Next;  /* Bypass deleted cell */
                free( TmpCell );
            }
        }
/* END */

/* START: fig3_12.txt */
        /* If X is not found, then Next field of returned value is NULL */
        /* Assumes a header */

        Position
        FindPrevious( ElementType X, List L )
        {
            Position P;

/* 1*/      P = L;
/* 2*/      while( P->Next != NULL && P->Next->Element != X )
/* 3*/          P = P->Next;

/* 4*/      return P;
        }
/* END */

/* START: fig3_13.txt */
        /* Insert (after legal position P) */
        /* Header implementation assumed */
        /* Parameter L is unused in this implementation */

        void
        Insert( ElementType X, List L, Position P )
        {
            Position TmpCell;

/* 1*/      TmpCell = malloc( sizeof( struct Node ) );
/* 2*/      if( TmpCell == NULL )
/* 3*/          FatalError( "Out of space!!!" );

/* 4*/      TmpCell->Element = X;
/* 5*/      TmpCell->Next = P->Next;
/* 6*/      P->Next = TmpCell;
        }
/* END */

#if 0
/* START: fig3_14.txt */
        /* Incorrect DeleteList algorithm */

        void
        DeleteList( List L )
        {
            Position P;

/* 1*/      P = L->Next;  /* Header assumed */
/* 2*/      L->Next = NULL;
/* 3*/      while( P != NULL )
            {
/* 4*/          free( P );
/* 5*/          P = P->Next;
            }
        }
/* END */
#endif

/* START: fig3_15.txt */
        /* Correct DeleteList algorithm */

        void
        DeleteList( List L )
        {
            Position P, Tmp;

/* 1*/      P = L->Next;  /* Header assumed */
/* 2*/      L->Next = NULL;
/* 3*/      while( P != NULL )
            {
/* 4*/          Tmp = P->Next;
/* 5*/          free( P );
/* 6*/          P = Tmp;
            }
        }
/* END */

        Position
        Header( List L )
        {
            return L;
        }

        Position
        First( List L )
        {
            return L->Next;
        }

        Position
        Advance( Position P )
        {
            return P->Next;
        }

        ElementType
        Retrieve( Position P )
        {
            return P->Element;
        }

int Insert2(ElementType X, List L, int idx)
{
	int i;
	Position p;

	p = L;
	for (i = 0; i < idx; i ++) {
		p = p->Next;
		if (! p) {
			printf("illegal index(%d)\n", idx);
			return -1;
		}
	}

	Insert(X, L, p);

	return 0;
}

int Delete2(List L, int idx)
{
	int i;
	ElementType x;
	Position p, t;

	p = L;
	for (i = 0; i < idx; i ++) {
		p = p->Next;
		if (! p || ! p->Next) {
			printf("illegal index(%d)\n", idx);
			return -1;
		}
	}

/*
	if (! p->Next)
		return -1;
*/

	t = p->Next;
	x = t->Element;
	p->Next = t->Next;
	free(t);

	return x;
}

void PrintList(List L)
{
	int i;
	Position p;

	p = L;
	for (i = 0; p->Next; i ++) {
		p = p->Next;
		printf("%02d:%d\n", i, p->Element);
	}
}

main()
{
	int i, j, x;
	List L;

	L = MakeEmpty(NULL);
	printf("L %s empty\n", IsEmpty(L) ? "is" : "is not");

	for (i = 0; i < 10; i ++)
		Insert2(i, L, i);
		
	Insert2(100, L, 11);
	Insert2(100, L, 0);
	Insert2(200, L, 11);

	for (i = 0, j = 0; ; i ++, j ++) {
		if (i % 2) {
			x = Delete2(L, j --);
			if (x == -1)
				break;
			printf("%02d:%d\n", i, x);
		}
	}

	PrintList(L);
	DeleteList(L);
}
