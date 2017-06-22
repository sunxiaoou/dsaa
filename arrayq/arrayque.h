#ifndef _ARRAYQUE_H_
#define _ARRAYQUE_H_

// #include <pthread.h>

#ifdef MYTEST
typedef struct ElemType {
	char cid[10];
	char buf[20];
	int flg;
} ElemType, *Element;
#endif

typedef void* QNode;

typedef struct arrayQue {
	int capacity;
	int front;
	int rear;
	int size;
	QNode *array;
//	pthread_mutex_t mutex;
} ArrayQue, *ArrayQPtr;

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

#endif /* _ARRAYQUE_H_ */
