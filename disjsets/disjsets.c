#include <stdio.h>

#include "disjsets.h"

/* #define SlowAlg */

/* START: fig8_7.txt */
        void
        Initialize( DisjSet S )
        {
            int i;

            for( i = NumSets; i > 0; i-- )
                S[ i ] = 0;
        }
/* END */

#ifdef SlowAlg
/* START: fig8_8.txt */
        /* Assumes Root1 and Root2 are roots */
        /* union is a C keyword, so this routine */
        /* is named SetUnion */

        void
        SetUnion( DisjSet S, SetType Root1, SetType Root2 )
        {
            S[ Root2 ] = Root1;
        }
/* END */

/* START: fig8_9.txt */
        SetType
        Find( int X, DisjSet S )
        {
            if( S[ X ] <= 0 )
                return X;
            else
                return Find( S[ X ], S );
        }
/* END */
#else

/* START: fig8_13.txt */
        /* Assume Root1 and Root2 are roots */
        /* union is a C keyword, so this routine */
        /* is named SetUnion */

        void
        SetUnion( DisjSet S, SetType Root1, SetType Root2 )
        {
            if( S[ Root2 ] < S[ Root1 ] ) /* Root2 is deeper set */
                S[ Root1 ] = Root2;  /* Make Root2 new root */
            else
            {
                if( S[ Root1 ] == S[ Root2 ] )  /* Same height, */
                    S[ Root1 ]--;               /* so update */
                S[ Root2 ] = Root1;
            }
        }
/* END */

/* START: fig8_15.txt */
        SetType
        Find( int X, DisjSet S )
        {
            if( S[ X ] <= 0 )
                return X;
            else
                return S[ X ] = Find( S[ X ], S );
        }
/* END */
#endif

void PrintDisjSet(int num, DisjSet S)
{
	int i;

	for (i = 0; i < (num < NumSets ? num : NumSets); i ++)
		printf("%d:%d ", i, S[i]);

	printf("\n");
}

#if MYTEST


main( )
{
    DisjSet S;
    int i, j, k, Set1, Set2;

    Initialize( S );
    j = k = 1;
    while( k <= 8 )
    {
        j = 1;
        while( j < NumSets )
        {
            Set1 = Find( j, S );
            Set2 = Find( j + k, S );
            SetUnion( S, Set1, Set2 );
            j += 2 * k;
        }
        k *= 2;
    }
    i = 1;
    for( i = 1; i <= NumSets; i++ )
    {
        Set1 = Find( i, S );
        printf( "%d**", Set1 );
    }
    printf( "\n" );
    return 0;
}

#endif
