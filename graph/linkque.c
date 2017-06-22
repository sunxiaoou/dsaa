#include <stdio.h>
#include <stdlib.h>

#include "linkque.h"

LinkQPtr CreateLinkQ(void)
{
	LinkQPtr Q;

	Q = malloc(sizeof(LinkQue));
	if (! Q) {
		printf("malloc failed\n");
		return NULL;
	}

	Q->head = malloc(sizeof(ListNode));
	if (! Q->head) {
		printf("malloc failed\n");
		return NULL;
	}

	Q->head->Next = NULL;
	Q->rear = Q->head;
	Q->size = 0;

	return Q;
}

void DestoryLinkQ(LinkQPtr Q)
{
	Position P, tmp;

	P = Q->head->Next;  /* Header assumed */
	Q->head->Next = NULL;
	while (P) {
		tmp = P->Next;
		free(P->data);
		free(P);
		P = tmp;
	}
	free(Q->head);
	free(Q);
}

int IsEmptyLinkQ(LinkQPtr Q)
{
	return Q->head->Next == NULL;
}

int IsLastLinkQ(Position P)
{
	return P->Next == NULL;
}

Position headLinkQ(LinkQPtr Q)
{
	return Q->head;
}

Position frontLinkQ(LinkQPtr Q)
{
	return Q->head->Next;
}

Position rearLinkQ(LinkQPtr Q)
{
	return Q->rear;
}

Position advanceLinkQ(Position P)
{
	return P->Next;
}

void *retrieveLinkQ(Position P)
{
	return P->data;
}

int EnqLinkQ(void *X, LinkQPtr Q)
{
	Position P;

	P = malloc(sizeof(struct ListNode));
	if(! P)
		return -1;

	P->data = X;
	P->Next = NULL;

	Q->rear->Next = P;
	Q->rear = P;

	Q->size ++;

	return 0;
}

void *DeqLinkQ(LinkQPtr Q)
{
	void *X;	
	Position P;

	if (IsEmptyLinkQ(Q))
		return NULL;

	P = Q->head->Next;
	X = P->data;
	Q->head->Next = P->Next;
	free(P);

	if (IsEmptyLinkQ(Q))
		Q->rear = Q->head;
	Q->size --;

	return X;
}

Position FindLinkQ(void *X, LinkQPtr Q)
{
	Position P;

	P = frontLinkQ(Q);
	while (P && Q->pCompare(X, P->data))
		P = P->Next;

	return P;
}

/* Insert node after the position */
Position InsertLinkQ(void *X, Position P, LinkQPtr Q)
{
	Position tmp;

	tmp = malloc(sizeof(struct ListNode));
	if (! tmp) {
		printf("malloc failed\n");
		return NULL;
	}

	tmp->data = X;
	tmp->Next = P->Next;
	P->Next = tmp;

	if (IsLastLinkQ(tmp))
		Q->rear = tmp;
	Q->size ++;

	return tmp;
}

/* Delete node after the position */
void *DeleteLinkQ(Position P, LinkQPtr Q)
{
	void *X;
	Position tmp;

	if (IsLastLinkQ(P))
		return NULL;

	tmp = P->Next;
	X = tmp->data;
	P->Next = tmp->Next;	/* Bypass deleted cell */
	free(tmp);

	if (IsLastLinkQ(P))
		Q->rear = P;
	Q->size --;

	return X;
}

void PrintLinkQ(LinkQPtr Q)
{
	Position P;

	P = headLinkQ(Q);
	while (P = P->Next)
		printf("%d ", Q->pValue(P->data));

	printf("\n");
}
