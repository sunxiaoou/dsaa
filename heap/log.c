#include <stdio.h>

int log_2(int x)
{
	int i;

	for (i = 0; x ; i ++)
		x >>= 1;

	return i - 1;
}

int pow_2(int x)
{
	int i, e;

	if (! x)
		return 1;

	for (i = 0, e = 1; i < x; i ++)
		e <<= 1;

	return e;
}

main()
{
	int i;

	for (i = 0; i < 10; i ++)
		printf("%d:%d ", pow_2(i), log_2(pow_2(i)));

	printf("\n");
}
