#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "prttree.h"
#include "searchtree.h"

void disorder(int A[], int num)
{
	int i, j, x;
   
	for (i = 0; i < num; i ++) {
		j = rand( ) % (i + 1);
		x = A[i];
		A[i] = A[j];
		A[j] = x;
	}
}

void printX(int X[], int num)
{
	int i;

	printf("X[]: ");
	for (i = 1; i <= num; i ++)
		printf("%d ", X[i]);

	printf("\n");
}

int deleteMax(SearchTree D)
{
	int X;

	X = Retrieve(FindMax(D));
	D = Delete(X, D);

	return X;
}

int check(int C, int X[], int num, int Left, int Right, SearchTree D)
{
	int i, j;
	int d, f;
	SearchTree T;

	struct Track {
		int d;
		int f;
	} track[20];	/* Maybe not enough, fix me */

	memset(track, 0, sizeof(track));
	printf("Check(%d) ", C);		

	for (i = 1; i <= num; i ++) {
		if (i < Left || i > Right) {
			d = abs(X[i] - C);
			printf("%d ", d);
			if (! (T = Find(d, D))) {
				printf("ko\n");
				return -1;
			}
			f = STFrequency(T);
			for (j = 0; j < 20; j ++) {
				if (! track[j].d) {
					track[j].d = d;
					track[j].f = 1;
					break;
				}
				if (track[j].d == d) {
					if (track[j].f < f) {
						track[j].f ++;
						break;
					}
					else {
						printf("ko\n");
						return -1;
					}
				}
			}
		}
	}

	printf("ok\n");

	return 0;
}

int Place(int X[], int num, int Left, int Right, SearchTree D)
{
	int rc = -1;
	int i, DMax;

	if (! D)
		return 0;

	printX(X, num);
	printf("D[]: ");
	PrintTree((TreePtr)D, 0);
	DMax = Retrieve(FindMax(D));

	/* Check if setting X[Right] = DMax is feasible. */
	printf("Right try X[%d] = %d\n", Right, DMax);
	rc = check(DMax, X, num, Left, Right, D);
	if (! rc) {
		X[Right] = DMax;
		for (i = 1; i < Left; i ++)
			D = Delete(abs(X[i] - X[Right]), D);
		for (i = Right + 1; i <= num; i ++)
			D = Delete(abs(X[i] - X[Right]), D);

		rc = Place(X, num, Left, Right - 1, D);
		if (rc == -1) {
			for (i = 1; i < Left; i ++)
				D = Insert(abs(X[i] - X[Right]), D);
			for (i = Right + 1; i <= num; i ++)
				D = Insert(abs(X[i] - X[Right]), D);
		}
		else
			return 0;
	}

	/* If first attempt failed, try to see if setting */
	/* X[Left] = X[Num] - DMax is feasible */

	printf("Left try X[%d] = %d\n", Left, X[num] - DMax);
	rc = check(X[num] - DMax, X, num, Left, Right, D);
	if (! rc) {
		X[Left] = X[num] - DMax;

		for (i = 1; i < Left; i ++)
			D = Delete(abs(X[i] - X[Left]), D);
		for (i = Right + 1; i <= num; i ++)
			D = Delete(abs(X[i] - X[Left]), D);

		rc = Place(X, num, Left + 1, Right, D);
		if (rc == -1) {
			for (i = 1; i < Left; i ++)
				D = Insert(abs(X[i] - X[Left]), D);
			for (i = Right + 1; i <= num; i ++)
				D = Insert(abs(X[i] - X[Left]), D);
		}
	}
	else 
		printf("Backtracking ...\n");


	return rc;
}

int Turnpike(int X[], SearchTree D, int num)
{
	int d;

	X[1] = 0;
	X[num] = deleteMax(D);
	X[num - 1] = deleteMax(D);
	d = X[num] - X[num - 1];

	if (! Find(d, D))
		return -1;

	D = Delete(d, D);
	return Place(X, num, 2, num - 2, D);
}

main()
{
/* |D| = N * (N - 1) / 2 */
	static int distset[] = { /* |D| = 15 */
		1, 2, 2, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 8, 10
	};
	
	static int X[7] = { /* N = 6 */
		-1, -1, -1, -1, -1, -1, -1
	};

	int i, num;
	SearchTree D;

	num = sizeof(distset) / sizeof(*distset);
	disorder(distset, num);

	D = MakeEmpty(NULL);
	for (i = 0; i < num; i ++)
		D = Insert(distset[i], D);

	pT2Str = ST2Str;
	pTNode = STElement;
	DrawTree((TreePtr)D, 0);

	if (! Turnpike(X, D, 6))
		printX(X, 6);
}
