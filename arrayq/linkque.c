#include <stdio.h>
#include <stdlib.h>

#include "linkque.h"

int lockLinkL(LinkLPtr ll)
{
	int rc;

	rc = pthread_mutex_lock(&ll->mutex);
	if (rc)	{
		fprintf(stderr, "pthread_mutex_lock failed(%s)\n", strerror(rc));
		return -1;
	}

	return 0;
}

int unlockLinkL(LinkLPtr ll)
{
	int rc;

	rc = pthread_mutex_unlock(&ll->mutex);
	if (rc)	{
		fprintf(stderr, "pthread_mutex_unlock failed(%s)\n", strerror(rc));
		return -1;
	}

	return 0;
}

LinkLPtr createLinkL(void)
{
	int rc;
	LinkLPtr ll;

	ll = malloc(sizeof(LinkList));
	if (! ll) {
		printf("malloc failed\n");
		return NULL;
	}

	ll->head = malloc(sizeof(LNode));
	if (! ll->head) {
		printf("malloc failed\n");
		return NULL;
	}

	ll->head->next = NULL;
	ll->rear = ll->head;
	ll->size = 0;

	rc = pthread_mutex_init(&ll->mutex, NULL);
	if (rc) {
		fprintf(stderr, "pthread_mutex_init failed(%s)\n", strerror(rc));
		free(ll);
		return NULL;
	}

	return ll;
}

void destoryLinkL(LinkLPtr ll)
{
	Position p, tmp;

	pthread_mutex_destroy(&ll->mutex);

	p = ll->head->next;  /* Header assumed */
	ll->head->next = NULL;
	while (p) {
		tmp = p->next;
		free(p->data);
		free(p);
		p = tmp;
	}
	free(ll->head);
	free(ll);
}

int isEmptyLinkL(LinkLPtr ll)
{
	return ll->head->next == NULL;
}

int isLastLinkL(Position p)
{
	return p->next == NULL;
}

Position headLinkL(LinkLPtr ll)
{
	return ll->head;
}

Position firstLinkL(LinkLPtr ll)
{
	return ll->head->next;
}

Position advanceLinkL(Position p)
{
	return p->next;
}

void *retrieveLinkL(Position p)
{
	return p->data;
}

/* Insert node after the position */
int insertLinkL(LinkLPtr ll, Position p, void *e)
{
	Position tmp;

	tmp = malloc(sizeof(struct LNode));
	if (! tmp) {
		printf("malloc failed\n");
		return -1;
	}

	tmp->data = e;
	tmp->next = p->next;
	p->next = tmp;

	if (isLastLinkL(tmp))
		ll->rear = tmp;
	ll->size ++;

	return 0;
}

/* Delete node after the position */
void *deleteLinkL(LinkLPtr ll, Position p)
{
	void *e;
	Position tmp;

	if (isLastLinkL(p))
		return NULL;

	tmp = p->next;
	e = retrieveLinkL(tmp);
	p->next = tmp->next;	/* Bypass deleted cell */
	free(tmp);

	if (isLastLinkL(p))
		ll->rear = p;
	ll->size --;

	return e;
}

/* LinkQueue functions */
Position frontLinkQ(LinkQPtr q)
{
	return q->head->next;
}

Position rearLinkQ(LinkQPtr q)
{
	return q->rear;
}

int lengthLinkQ(LinkQPtr q)
{
	return q->size;
}

int enqLinkQ(LinkQPtr q, void *e)
{
	int rc;

	rc = insertLinkL(q, rearLinkQ(q), e);
	return rc;
}

void *deqLinkQ(LinkQPtr q)
{
	void *e;

	e = deleteLinkL(q, headLinkL(q));
	return e;
}


#ifdef MYTEST
void printLinkL(const LinkLPtr ll)
{
	Element e;
	Position p = headLinkL(ll);

	if (isEmptyLinkL(ll)) {
		printf("Empty list\n");
		return;
	}

	do {
		p = advanceLinkL(p);
		e = retrieveLinkL(p);
		printf("%d ", atoi(e->cid));
	} while (! isLastLinkL(p));

	printf("\n");
}

Element create_elem(int i)
{
	Element e;

	e = malloc(sizeof(ElemType));
	sprintf(e->cid, "%08d", i);
	sprintf(e->buf, "%08d", i);
	e->flg = rand() % 10 ? 0 : 1;

	return e;
}


test_ll()
{
    int i;
    LinkLPtr L;
    Position p, p2;
	Element e;

    L = createLinkL();
    p = headLinkL( L );
    printLinkL( L );

    for( i = 0; i < 10; i++ )
    {
        insertLinkL(L, p, create_elem(i));
        printLinkL(L);
        p = advanceLinkL(p);
    }

/* delete even nodes */
    p = headLinkL( L );
	do {
		p2 = advanceLinkL(p);
		e = retrieveLinkL(p2);
		if (! (atoi(e->cid) % 2))
			deleteLinkL(L, p);
		p = p2;
	} while (! isLastLinkL(p));
		
    printf( "Finished deletions\n" );

    printLinkL( L );

    destoryLinkL( L );

    return 0;
}

test_lq()
{
    int i;
    LinkQPtr Q;
	Element e;

    Q = createLinkL();

    for( i = 0; i < 10; i++ )
        enqLinkQ(Q, create_elem(i));

	printLinkL(Q);

    while(! isEmptyLinkL(Q))
    {
        e = deqLinkQ(Q);
		printf("%d\n", atoi(e->cid));
    }

	printLinkL(Q);

    for( i = 0; i < 10; i++ )
        enqLinkQ(Q, create_elem(i));

	printLinkL(Q);

    for( i = 0; i < 5; i++ )
    {
        e = deqLinkQ(Q);
		printf("%d\n", atoi(e->cid));
    }

	printLinkL(Q);

    destoryLinkL( Q );
    return 0;
}

main()
{
//	test_ll();
	test_lq();
}
#endif
