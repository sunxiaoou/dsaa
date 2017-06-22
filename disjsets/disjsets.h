#ifndef _DisjSet_H

#define NumSets 128

typedef int DisjSet[NumSets + 1];
typedef int SetType;

void Initialize(DisjSet S);
void SetUnion(DisjSet S, SetType Root1, SetType Root2);
SetType Find(int X, DisjSet S);

void PrintDisjSet(int num, DisjSet S);
#endif  /* _DisjSet_H */
