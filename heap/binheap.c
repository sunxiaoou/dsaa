        #include "binheap.h"
        #include "fatal.h"
        #include <string.h>
        #include <stdlib.h>

        #define MinPQSize (10)
        #define MinData (-32767)

/* START: fig6_0.txt */
        PriorityQueue
        Initialize( int MaxElements )
        {
            PriorityQueue H;

/* 1*/      if( MaxElements < MinPQSize )
/* 2*/          Error( "Priority queue size is too small" );

/* 3*/      H = malloc( sizeof( struct HeapStruct ) );
/* 4*/      if( H ==NULL )
/* 5*/          FatalError( "Out of space!!!" );

            /* Allocate the array plus one extra for sentinel */
/* 6*/      H->Elements = malloc( ( MaxElements + 1 )
                                    * sizeof( ElementType ) );
/* 7*/      if( H->Elements == NULL )
/* 8*/          FatalError( "Out of space!!!" );

/* 9*/      H->Capacity = MaxElements;
/*10*/      H->Size = 0;
/*11*/      H->Elements[ 0 ] = MinData;

/*12*/      return H;
        }
/* END */

        void
        MakeEmpty( PriorityQueue H )
        {
            H->Size = 0;
        }

/* START: fig6_8.txt */
        /* H->Element[ 0 ] is a sentinel */

        void
        Insert( ElementType X, PriorityQueue H )
        {
            int i;

            if( IsFull( H ) )
            {
                Error( "Priority queue is full" );
                return;
            }

            for( i = ++H->Size; H->Elements[ i / 2 ] > X; i /= 2 )
                H->Elements[ i ] = H->Elements[ i / 2 ];
            H->Elements[ i ] = X;
        }
/* END */

/* START: fig6_12.txt */
        ElementType
        DeleteMin( PriorityQueue H )
        {
            int i, Child;
            ElementType MinElement, LastElement;

/* 1*/      if( IsEmpty( H ) )
            {
/* 2*/          Error( "Priority queue is empty" );
/* 3*/          return H->Elements[ 0 ];
            }
/* 4*/      MinElement = H->Elements[ 1 ];
/* 5*/      LastElement = H->Elements[ H->Size-- ];

/* 6*/      for( i = 1; i * 2 <= H->Size; i = Child )
            {
                /* Find smaller child */
/* 7*/          Child = i * 2;
/* 8*/          if( Child != H->Size && H->Elements[ Child + 1 ]
/* 9*/                                < H->Elements[ Child ] )
/*10*/              Child++;

                /* Percolate one level */
/*11*/          if( LastElement > H->Elements[ Child ] )
/*12*/              H->Elements[ i ] = H->Elements[ Child ];
                else
/*13*/              break;
            }
/*14*/      H->Elements[ i ] = LastElement;
/*15*/      return MinElement;
        }
/* END */

        ElementType
        FindMin( PriorityQueue H )
        {
            if( !IsEmpty( H ) )
                return H->Elements[ 1 ];
            Error( "Priority Queue is Empty" );
            return H->Elements[ 0 ];
        }

        int
        IsEmpty( PriorityQueue H )
        {
            return H->Size == 0;
        }

        int
        IsFull( PriorityQueue H )
        {
            return H->Size == H->Capacity;
        }

        void
        Destroy( PriorityQueue H )
        {
            free( H->Elements );
            free( H );
        }

        #if 0
/* START: fig6_14.txt */
        for( i = N / 2; i > 0; i-- )
            PercolateDown( i );
/* END */
        #endif

void PercolateDown(int idx, PriorityQueue H)
{
	int i, Child;
	ElementType tmp;

	for (i = idx; i * 2 <= H->Size; i = Child) {
		Child = i * 2;
		if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
			Child ++;

		if (H->Elements[Child] < H->Elements[i]) {
			tmp = H->Elements[i];
			H->Elements[i] = H->Elements[Child];
			H->Elements[Child] = tmp;
		}
	}			
}

void BuildHeap(PriorityQueue H)
{
	int i;

	for (i = H->Size / 2; i > 0; i --)
		PercolateDown(i, H);					
}

typedef struct dot {
	int val;
	int col;
} DOT;

typedef struct {
	int idx;
	DOT dot[100];
} ArrayD;

void appendArray(ArrayD *a, int v, int c)
{
	if (a->idx == 79) {
		printf("overflow max column\n");
		return;
	}

	a->dot[a->idx].val = v;
	a->dot[a->idx].col = c;

	a->idx ++;
}

void printArray(ArrayD *a)
{
	int i, j;
	int off = 0;

	for (j = 0; j < a->idx; j ++) {
		for (i = 0; i < a->dot[j].col - off; i ++)
			putchar(' ');
		printf("%02d", a->dot[j].val);
		off = a->dot[j].col + 2;
	}

	printf("\n");
}

void printAll(ArrayD *buf, int num)
{
	int i;

	for (i = 0; i < num; i ++) {
		if (buf[i].idx)
			printArray(&buf[i]);
	}
}

int log_2(int x)
{
	int i;

	for (i = 0; x ; i ++)
		x >>= 1;

	return i - 1;
}

void PrintTree(PriorityQueue H, int tree)
{
	static int col;
	static int bufsize;
	static ArrayD *buffer;
	int i, depth;

	if (tree > H->Size)
		return;

	if (tree == 1) {
		col = 0;
		bufsize = 0;
		buffer = NULL;
	}

	depth = log_2(tree);
	if (bufsize < depth + 1) {
		i = bufsize;
		bufsize += 10;
		buffer = realloc(buffer, sizeof(ArrayD) * bufsize);
		for (; i < bufsize; i ++)
			buffer[i].idx = 0;
	}

	PrintTree(H, tree * 2);
	appendArray(&buffer[depth], H->Elements[tree], col);
	col += 2;
	PrintTree(H, tree * 2 + 1);

	if (tree == 1) {
		printAll(buffer, bufsize);
		printf("\n");
		free(buffer);
	}
}
