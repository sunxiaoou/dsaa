#include <stdio.h>
#include <stdlib.h>

main()
{
	int i;

	for (i = 0; i < 10; i ++)
		printf("%d ", rand() % 100);
	printf("\n");

	srand(1);
	for (i = 0; i < 10; i ++)
		printf("%d ", rand() % 100);
	printf("\n");
}
