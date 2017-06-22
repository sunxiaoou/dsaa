#include <stdio.h>
#include <stdlib.h>

#include "arrayque.h"

#define MinArrayQSize 5

int isEmptyArrayQ(ArrayQPtr Q)
{
	return Q->size == 0;
}

int isFullArrayQ(ArrayQPtr Q)
{
	return Q->size == Q->capacity;
}

int lengthArrayQ(ArrayQPtr Q)
{
	return Q->size;
}

void emptyArrayQ(ArrayQPtr Q)
{
	Q->size = 0;
	Q->front = 1;
	Q->rear = 0;
}

static int incCircle(int cap, int i)
{
//	return (i + 1) % cap;
	if (++ i == cap)
		i = 0;
	return i;
}

static int decCircle(int cap, int i)
{
	if (-- i == -1)
		i = cap;
	return i;
}

int enqArrayQ(ArrayQPtr Q, QNode x)
{
	if (isFullArrayQ(Q))
		return -1;

	Q->size ++;
	Q->rear = incCircle(Q->capacity, Q->rear);
	Q->array[Q->rear] = x;
	return 0;	
}

int enq2ArrayQ(ArrayQPtr Q, QNode x)
{
	int rc = 0;

	if (isFullArrayQ(Q)) {
		free(Q->array[Q->front]);
		Q->front = incCircle(Q->capacity, Q->front);
		rc = 1;
	}
	else
		Q->size ++;

	Q->rear = incCircle(Q->capacity, Q->rear);
	Q->array[Q->rear] = x;

	return rc;
}

QNode frontArrayQ(ArrayQPtr Q)
{
	if (isEmptyArrayQ(Q))
		return NULL;

	return Q->array[Q->front];
}

QNode peekArrayQ(ArrayQPtr Q, int idx)
{
	if (isEmptyArrayQ(Q))
		return NULL;

	if (idx >= lengthArrayQ(Q))
		return NULL;

	return Q->array[(Q->front + idx) % Q->capacity];
}

QNode deqArrayQ(ArrayQPtr Q)
{
	QNode x;

	if (isEmptyArrayQ(Q))
		return NULL;

	Q->size --;
	x = Q->array[Q->front];
	Q->front = incCircle(Q->capacity, Q->front);

	return x;
}

ArrayQPtr createArrayQ(int num)
{
	ArrayQPtr Q;

	Q = malloc(sizeof(ArrayQue));
	if (! Q) {
		printf("malloc failed\n");
		return NULL;
	}

	Q->capacity = MinArrayQSize < num ? num : MinArrayQSize;
	Q->array = malloc(sizeof(QNode) * Q->capacity);
	if(! Q->array) {
		printf("malloc failed\n");
		return NULL;
	}
	emptyArrayQ(Q);

	return Q;
}

void destoryArrayQ(ArrayQPtr Q)
{
	if (Q) {
		while(! isEmptyArrayQ(Q))
			free(deqArrayQ(Q));
		free(Q->array);
		free(Q);
	}
}

#ifdef MYTEST
/*
void printArrayQ(ArrayQPtr Q)
{
	int i, j;
	Element e;

	if (isEmptyArrayQ(Q)) {
		printf("Empty queue\n");
		return;
	}

	for (i = 0, j = Q->front; i < lengthArrayQ(Q);
	   	i ++, j = incCircle(Q->capacity, j))
	{
		e = Q->array[j];
		printf("%d ", atoi(e->cid));
	}

	printf("\n");
}
*/

void printArrayQ(ArrayQPtr Q)
{
	int i;
	Element e;

	if (isEmptyArrayQ(Q)) {
		printf("Empty queue\n");
		return;
	}

	i = 0;
	while (e = peekArrayQ(Q, i ++))
		printf("%d ", atoi(e->cid));

	printf("\n");
}

int isInArrayQ(ArrayQPtr Q, int idx)
{
	if (isEmptyArrayQ(Q))
		return 0;

	if (Q->front <= Q->rear)
		return idx >= Q->front && idx <= Q->rear;
	else
		return idx >= Q->front || idx <= Q->rear;
}

void dumpArrayQ(ArrayQPtr Q)
{
	int i;
	Element e;

	printf("F%dR%d\n", Q->front, Q->rear);
	for (i = 0; i < Q->capacity; i ++) {
		if (isInArrayQ(Q, i)) {
			e = Q->array[i];
			printf("%02d:%d ", i, atoi(e->cid));
		}
		else
			printf("%02d:-1 ", i);
	}
	printf("\n");
}

Element create_elem(int i)
{
	Element e;

	e = malloc(sizeof(ElemType));
	sprintf(e->cid, "%08d", i);
	sprintf(e->buf, "%08d", i);
//	e->flg = rand() % 10 ? 0 : 1;
	e->flg = i < 5 ? 1 : 0;

	return e;
}

main()
{
	int i;
	int nD = 0, nE = 0;
	ArrayQPtr Q;
	Element e;

	Q = createArrayQ(12);

	for( i = 0; i < 20; i++ ) {
		if (enq2ArrayQ(Q, create_elem(i)))
			nD ++;
		nE ++;
	}

	printArrayQ(Q);
	dumpArrayQ(Q);

	while(! isEmptyArrayQ(Q))
	{
		e = deqArrayQ(Q);
		printf("%d\n", atoi(e->cid));
		nD ++;
	}

	printArrayQ(Q);
//	dumpArrayQ(Q);

	for( i = 0; i < 10; i++ ) {
		enqArrayQ(Q, create_elem(i));
		nE ++;
	}

	printArrayQ(Q);
//	dumpArrayQ(Q);

	for (i = 0; i < lengthArrayQ(Q); i++) {
		e = frontArrayQ(Q);
		if (e->flg) {
			deqArrayQ(Q);
			nD ++;
		}
		else
			break;
	}

	i = 0;
	while (e = peekArrayQ(Q, i ++))
		printf("%d\n", atoi(e->cid));

	printArrayQ(Q);
	dumpArrayQ(Q);

	printf("len(%d)\n", lengthArrayQ(Q));
	printf("nE(%d)nD(%d)\n", nE, nD);
	destoryArrayQ( Q );
	return 0;
}
#endif
