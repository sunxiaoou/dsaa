#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "msort.h"

#define Min(x , y) (x < y ? x : y)
#define Max(x , y) (x < y ? y : x)

typedef struct Point {
	int x;
	int y;
} Point, *PoiPtr;

typedef struct Result {
	int d;
	PoiPtr a, b;
} Result;

int compareX(void *a, void *b)
{
	if (! a || ! b)
		return 0;

	return ((PoiPtr)a)->x - ((PoiPtr)b)->x;
}

int compareY(void *a, void *b)
{
	if (! a || ! b)
		return 0;

	return ((PoiPtr)a)->y - ((PoiPtr)b)->y;
}

int distance(PoiPtr a, PoiPtr b)
{
	int i;
	int x, y;

	x = a->x - b->x;
	y = a->y - b->y;

	for (i = 1; i * i <= x * x + y * y; i ++);

	return i - 1;
}

int printpois(PoiPtr P[], int num)
{
	int i;

	for (i = 0; i < num; i ++)
		printf("%d,%d  ", P[i]->x, P[i]->y);
	printf("\n");
}

int Closest(PoiPtr P[], PoiPtr Q[], int Left, int Right)
{
    int i, j, k, num;
	int Center;
	int d, d2;
	PoiPtr a, b;

	num =  Right - Left + 1;
//	printpois(&P[Left], num);

	if (num == 1)
		return 0x7fffffff;

	if (num == 2) {
		Q[0] = P[Left]; Q[1] = P[Right];
		return distance(P[Left], P[Right]);
	}

	Center = (Left + Right) / 2;

	d = Closest(P, Q, Left, Center);
	a = Q[0]; b = Q[1];
//	printf("dL: %d\n", d);
	d2 = Closest(P, Q, Center + 1, Right);
//	printf("dR: %d\n", d2);
	if (d > d2) {
		d = d2;
		a = Q[0]; b = Q[1];
	}

	for  (i = Left, k = 0; i <= Right; i ++)
		if (abs(P[i]->x - P[Center]->x) < d)
			Q[k ++] = P[i];
//	printpois(Q, k);
			
	for (i = 0; i < k; i ++) {
		for (j = i + 1; j < k; j ++) {
			d2 = distance(Q[i], Q[j]);
			if (d > d2) {
				d = d2;
				a = Q[i]; b = Q[j];
			}
		}
	}

	Q[0] = a; Q[1] = b;
//	printf("d: %d\n", d);
	return d;
}

void ClosestPoints(Point pois[], int num, Result *res)
{
	int i;
	PoiPtr *P, *Q;

	P = malloc(sizeof(ElementType) * num);
	assert(P);
	Q = malloc(sizeof(ElementType) * num);
	assert(Q);

	for (i = 0; i < num; i ++)
		P[i] = &pois[i];

	pCompare = compareX;
	Mergesort((ElementType)P, num);

//	printpois(P, num);

	res->d = Closest(P, Q, 0, num - 1);
	res->a = Q[0];
	res->b = Q[1];
}

void DrawPoints(Point pois[], int num) 
{
	char **a;
	char s[4];
	int cols, rows;
	int i, j;
	PoiPtr *P;

	P = malloc(sizeof(ElementType) * num);
	assert(P);
	for (i = 0; i < num; i ++)
		P[i] = &pois[i];

	pCompare = compareY;
	Mergesort((ElementType)P, num);

	for (i = cols = rows = 0 ; i < num; i ++) {
		cols = Max(cols, pois[i].x);
		rows = Max(rows, pois[i].y);
	}
	cols = cols * 3 + 1;
   	rows ++;

	a = malloc(sizeof(char *) * rows);
	assert(a);
	for (i = j = 0; i < rows; i ++) {
		a[i] = malloc(cols);
		assert(a[i]);
		memset(a[i], ' ', cols);

		while (j < num && P[j]->y == i) {
			sprintf(s, "%02d%02d", P[j]->x, P[j]->y);
			memcpy(&a[i][(P[j]->x) * 3], s, 4);
			j ++;
		}
		a[i][cols - 1] = 0;
	}

	printf("There are %d Points\n", num);
	for (i = rows - 1; i >= 0; i --)
		puts(a[i]);
}

main()
{
	static Point pois[] = {
		0, 14, 1, 5, 3, 18, 4, 0, 4, 15, 7, 2, 8, 10, 8, 16, 
		9, 6, 10, 16, 12, 1, 12, 11, 15, 19, 16, 3, 17, 14, 19, 9
	};
	int num;
	Result res;

	num = sizeof(pois) / sizeof(*pois);

	DrawPoints(pois, num);

	ClosestPoints(pois, num, &res);

	printf("\nClosest points are %02d%02d and %02d%02d, distance is %d\n",
		res.a->x, res.a->y, res.b->x, res.b->y, res.d);
}
