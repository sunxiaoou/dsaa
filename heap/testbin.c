#include "binomial.h"
#include <stdio.h>

#define MaxSize (12000)

main( )
{
    BinQueue H;
    int i, j;

    H = Initialize( );
    for( i=0, j=MaxSize/2; i<MaxSize; i++, j=( j+71)%MaxSize )
    {
        H = Insert( j, H );
    }
    j = 0;
    while( !IsEmpty( H ) )
    {
        if( DeleteMin( H ) != j++ )
            printf( "Error in DeleteMin, %d\n", j );
    }
    if( j != MaxSize )
        printf( "Error in counting\n" );

	for (i = 0; i < 20; i ++)  {
		j = rand() % 100;
        Insert( j, H );
		printf("insert %d\n", j);
	}
	PrintBin(H);

    while(! IsEmpty(H)) {
		printf("delete %d\n", DeleteMin(H));
//		PrintBin(H);
	}
}
