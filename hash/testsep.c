#include <stdio.h>
#include "hashsep.h"

#define NumItems 400

main( )
{
    HashTable H;
    Position P;
    int i;
    int j = 0;
    int CurrentSize;

    H = InitializeTable( CurrentSize = 13 );

    for( i = 0; i < NumItems; i++, j += 71 )
        Insert( j, H );
	PrintTable(H);

    for( i = 0, j = 0; i < CurrentSize; i++, j += 71 )
		Delete(j, H);	

    for( i = 0, j = 0; i < NumItems; i++, j += 71 )
        if( ( P = Find( j, H ) ) == NULL || Retrieve( P ) != j )
            printf( "Error at %d\n", j );

    printf( "End of program.\n" );
    return 0;
}
