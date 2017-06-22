#ifndef _HUFFTREE_H
#define _HUFFTREE_H

typedef struct Character {
	char value;
	char code[8];
	long frequency;
	long totalbits; 
} Character, *CharPtr;

typedef struct HuffNode {
	struct HuffNode *Left;
	struct HuffNode *Right;
	CharPtr C;
} HuffNode, *Position, *HuffPtr;

HuffPtr InitTree(CharPtr C);
HuffPtr MergeTree(HuffPtr A, HuffPtr B);
void EncodeTree(HuffPtr T, char *code, int isRight);

#endif  /* _HUFFTREE_H */
