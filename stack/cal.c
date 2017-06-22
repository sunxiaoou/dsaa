#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stackar.h"

int opLevel(char op)
{
	switch (op) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '(':
			return 3;
		default:
			return -1;
	}
}

void infix2postfix(char *in, char *post)
{
	char c;
	char *p1 = in;
	char *p2 = post;
	Stack S;

	S = CreateStack(12);
	while (*p1) {
		switch (*p1) {
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
				while(! IsEmpty(S)) {
					c = Top(S);
					if (c == '(' || opLevel(c) < opLevel(*p1))
						break;
					*(p2 ++) = c;
					Pop(S);
				}
				*(p2 ++) = ' ';
				Push(*p1, S);
				break;
			case ')':
				while(! IsEmpty(S)) {
					c = TopAndPop(S);
					if (c == '(')
						break;
					*(p2 ++) = c;
				}
				break;
			default:
				if (isalpha(*p1) || isdigit(*p1)) 
					*(p2 ++) = *p1;
				break;
		}
		p1 ++;
	}

	while(! IsEmpty(S))
		*(p2 ++) = TopAndPop(S);

	*p2 = 0;

	DisposeStack(S);
}

int calculator(char *post)
{
	char *p = post;
	int x;
	Stack S;

	S = CreateStack(12);
	while(*p) {
		switch (*p) {
			case '+':
				x = TopAndPop(S);
				Push(TopAndPop(S) + x, S);
//				printf("%d\n", Top(S));
				break;
			case '-':
				x = TopAndPop(S);
				Push(TopAndPop(S) - x, S);
//				printf("%d\n", Top(S));
				break;
			case '*':
				x = TopAndPop(S);
				Push(TopAndPop(S) * x, S);
//				printf("%d\n", Top(S));
				break;
			case '/':
				x = TopAndPop(S);
				Push(TopAndPop(S) / x, S);
//				printf("%d\n", Top(S));
				break;
			default:
				if (isdigit(*p)) {
					Push(atoi(p), S);
					while (isdigit(*p))
						p ++;
					p --;
				}
				break;
		}
		p ++;
	}

	x = Top(S);
	DisposeStack(S);

	return x;
}

main()
{
	char s[] = "365 + 12 * 4 + (7 * 98 + 314) * 30";
//	char s[] = "365 - 12 - 4";
	char s2[80];

	infix2postfix(s, s2);
	printf("%s\n", s);
	printf("%s\n", s2);

	printf("result(%d)\n", calculator(s2));
}
