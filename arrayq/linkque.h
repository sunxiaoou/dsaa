#ifndef _LINKQUE_H_
#define _LINKQUE_H_

#include <pthread.h>

#ifdef MYTEST
typedef struct ElemType {
	char cid[10];
	char buf[20];
	int flg;
} ElemType, *Element;
#endif

typedef struct LNode {
	void *data;
	struct LNode *next;
} LNode, *Position;

typedef struct LinkList {
	Position head;	/* front is always head->next */
	Position rear;
	int size;
	pthread_mutex_t mutex;
} LinkList, *LinkLPtr, *LinkQPtr;; 

/*
int lockLinkL(LinkLPtr ll);
int unlockLinkL(LinkLPtr ll);
LinkLPtr createLinkL(void);
void destoryLinkL(LinkLPtr ll);
int insertLinkL(LinkLPtr ll, int idx, void *e);
void *peekLinkL(LinkLPtr ll, int idx);
void *deleteLinkL(LinkLPtr ll, int idx);
int linkLLength(LinkLPtr ll);
void printLinkL(LinkLPtr ll);

int enqLinkQ(LinkQPtr q, void *e);
void *deqLinkQ(LinkQPtr q);
*/

#endif /* _LINKQUE_H_ */
