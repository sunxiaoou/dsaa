#include <stdio.h>

static int NextPrime( int N )
{
	int i;

	if( N % 2 == 0 )
		N++;
	for( ; ; N += 2 ) {
		for( i = 3; i * i <= N; i += 2 ) {
			if( N % i == 0 )
				goto ContOuter;  /* Sorry about this! */
		}
		return N;
ContOuter:
		;
	}
}

main()
{
	int i, j;

	for (i = 0, j = 100; i < 20; i ++, j ++)
		printf("%d ", j = NextPrime(j)); 

	printf("\n");
}
