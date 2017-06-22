#ifndef _LINKQUE_H_
#define _LINKQUE_H_

typedef struct ListNode {
    void *data;
    struct ListNode *Next;
} ListNode, *Position, *List;

typedef struct LinkQue {
	int size;
	Position rear;
	List head;	/* front is always head->next */
	int (*pValue)(void *);
	int (*pCompare)(void *, void *);
} LinkQue, *LinkQPtr;


LinkQPtr CreateLinkQ(void);
void DestoryLinkQ(LinkQPtr Q);
int IsEmptyLinkQ(LinkQPtr Q);
int IsLastLinkQ(Position P);
Position headLinkQ(LinkQPtr Q);
Position frontLinkQ(LinkQPtr Q);
Position rearLinkQ(LinkQPtr Q);
Position advanceLinkQ(Position P);
void *retrieveLinkQ(Position P);
int EnqLinkQ(void *X, LinkQPtr Q);
void *DeqLinkQ(LinkQPtr Q);
Position FindLinkQ(void *X, LinkQPtr Q);
Position InsertLinkQ(void *X, Position P, LinkQPtr Q);
void *DeleteLinkQ(Position P, LinkQPtr Q);
void PrintLinkQ(LinkQPtr Q);

#endif /* _LINKQUE_H_ */
