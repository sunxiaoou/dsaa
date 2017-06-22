#include <stdio.h>
#include <stdlib.h>

#include "leftheap.h"

#define MaxSize 5000

main( )
{
    PriorityQueue H;
    int i, j;

    H = Initialize( );
    for( i=0, j=MaxSize/2; i<MaxSize; i++, j=( j+17)%MaxSize )
        Insert( j, H );

    j = 0;
    while( !IsEmpty( H ) )
        if( FindMin( H ) != j++ )
            printf( "Error in DeleteMin, %d\n", j );
        else
            H = DeleteMin1( H );

	for (i = 0; i < 20; i ++)  {
		j = rand() % 100;
        Insert( j, H );
		printf("insert %d\n", j);
		PrintTree(H, 0);
	}

    while(! IsEmpty(H)) {
		printf("delete %d\n", H->Element);
		H = DeleteMin1(H);
		PrintTree(H, 0);
	}

	printf("\n");

    printf( "Done...\n" );
    return 0;
}
