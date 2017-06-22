#include <stdio.h>

#include "prttree.h"
#include "redblack.h"

// #define N 800
#define NumItems 50

int main()
{
	static int x[] = {
		10, 85, 15, 70, 20, 60, 30, 50,	65,
		80, 90, 40, 5, 55, 45, 75
	};

    RedBlackTree T;
    Position P;
    int i, j;


	pT2Str = Node2Str;
	pNullNode = GetNullNode;	

    T = Initialize();
    T = MakeEmpty( T );

#if 0
	j = sizeof(x) / sizeof(*x);
	for (i = 0; i <  j; i ++) {
        T = Insert(x[i], T);
	}
	DrawTree((TreePtr)(T->Right), 0);

	for (i = j - 1; i >= 0; i --) {
		printf("Remove %d\n", x[i]);
		Remove(x[i], T);
		DrawTree((TreePtr)(T->Right), 0);
		if ((Check(T, T->Right)) == -1) {
			printf("Remove %d failed\n", x[i]);
			break;
		}
	}

	return 0;
#endif

	j = 0;
    for( i = 0; i < NumItems; i++, j = ( j + 7 ) % NumItems )
        T = Insert( j, T );
    printf( "Inserts are complete\n" );
	if (Check(T, T->Right) == -1)
		printf("Insert check failed\n");
	DrawTree((TreePtr)(T->Right), 0);

    for( i = 0; i < NumItems; i++ )
        if( ( P = Find( i, T ) ) == NULL || Retrieve( P ) != i )
            printf( "Error at %d\n", i );

    printf( "Entering remove\n" );
    for (i = 0; i < NumItems; i += 2) {
		Remove(i, T);
		if (Check(T, T->Right) == -1) {
			printf("Remove %d failed\n", i);
			DrawTree((TreePtr)(T->Right), 0);
			break;
		}
	}
	DrawTree((TreePtr)(T->Right), 0);

    for( i = 1; i < NumItems; i += 2 )
    {
        P = Find( i, T );
        if( Retrieve( P ) != i )
            printf( "Error2 at %d\n", i );
    }

    for( i = 0; i < NumItems; i += 2 )
    {
        P = Find( i, T );
        if( Retrieve( P ) == i )
            printf( "Error3 at %d\n", i );
    }

    printf( "Min is %d, Max is %d\n", Retrieve( FindMin( T ) ),
               Retrieve( FindMax( T ) ) );
}
