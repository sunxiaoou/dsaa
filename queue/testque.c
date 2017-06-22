#include <stdio.h>
#include "queue.h"

main( )
{
    Queue Q;
    int i;

    Q = CreateQueue( 12 );

    for( i = 0; i < 10; i++ )
        Enqueue( i, Q );

	printQueue(Q);

    while( !IsEmpty( Q ) )
    {
        printf( "%d\n", Front( Q ) );
        Dequeue( Q );
    }

    for( i = 0; i < 10; i++ )
        Enqueue( i, Q );

	printQueue(Q);

    for( i = 0; i < 10; i++ )
    {
        printf( "%d\n", Front( Q ) );
        Dequeue( Q );
    }

	printQueue(Q);

    DisposeQueue( Q );
    return 0;
}
