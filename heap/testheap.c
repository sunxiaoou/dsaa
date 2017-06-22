#include <stdio.h>
#include <stdlib.h>
#include "binheap.h"

#define MaxSize (1000)

main( )
{
    PriorityQueue H;
    int i, j;
	int a[] = {
		150, 80, 40, 30, 10, 70, 110,
	   	100, 20, 90, 60, 50, 120, 140, 130
	};

    H = Initialize( MaxSize );
    for( i=0, j=MaxSize/2; i<MaxSize; i++, j=( j+71)%MaxSize )
        Insert( j, H );

    j = 0;
    while( !IsEmpty( H ) )
        if( DeleteMin( H ) != j++ )
            printf( "Error in DeleteMin, %d\n", j );

	for (i = 0; i < 20; i ++)  {
		j = rand() % 100;
        Insert( j, H );
		printf("insert %d\n", j);
		PrintTree(H, 1);
	}

    while(! IsEmpty(H)) {
		printf("delete %d\n", DeleteMin(H));
		PrintTree(H, 1);
	}

	printf("\n");

	j = sizeof(a) / sizeof(*a);
	for (i = 0; i < j; i ++)
		H->Elements[i + 1] = a[i];
	H->Size = j;
	PrintTree(H, 1);
	BuildHeap(H);
	PrintTree(H, 1);
}
