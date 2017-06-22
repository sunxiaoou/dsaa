#include <stdio.h>

#include "prttree.h"
#include "splay.h"

#define NumItems 50

main( )
{
	static int x[] = {
		10, 85, 15, 70, 20, 60, 30, 50,	65,
		80, 90, 40, 5, 55, 45, 75
	};
    SplayTree T;
    SplayTree P;
    int i, j;

	pT2Str = Node2Str;
	pNullNode = GetNullNode;	

    T = Initialize();
    T = MakeEmpty(T);

	j = sizeof(x) / sizeof(*x);
	for (i = 0; i <  j; i ++) {
        T = Insert(x[i], T);
	}
	DrawTree((TreePtr)T, 0);

	for (i = j - 1; i >= 0; i --) {
		printf("Remove %d\n", x[i]);
		T = Remove(x[i], T);
		DrawTree((TreePtr)T, 0);
	}

	return 0;

	j = 0;
    for( i = 0; i < NumItems; i++, j = ( j + 7 ) % NumItems ) {
		printf("Insert %d\n", j);
        T = Insert( j, T );
		DrawTree((TreePtr)T, 0);
	}
  
    for( j = 0; j < 2; j++ )
        for( i = 0; i < NumItems; i++ )
        {
            T = Find( i, T );
            if( Retrieve( T ) != i )
                printf( "Error1 at %d\n", i );
        }

    printf( "Entering remove\n" );

    for( i = 0; i < NumItems; i += 2 )
        T = Remove( i, T );

    for( i = 1; i < NumItems; i += 2 )
    {
        T = Find( i, T );
        if( Retrieve( T ) != i )
            printf( "Error2 at %d\n", i );
    }

    for( i = 0; i < NumItems; i += 2 )
    {
        T = Find( i, T );
        if( Retrieve( T ) == i )
            printf( "Error3 at %d\n", i );
    }

    printf( "Min is %d\n", Retrieve( T = FindMin( T ) ) );
    printf( "Max is %d\n", Retrieve( T = FindMax( T ) ) );

    return 0;
}
