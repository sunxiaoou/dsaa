#ifndef _MSORT_H
#define _MSORT_H

typedef void* ElementType;

int (*pCompare)(ElementType, ElementType);

void Mergesort(ElementType A[ ], int N);

#endif  /* _MSORT_H */
