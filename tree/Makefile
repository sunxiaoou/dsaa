
EXES= testavl testrb testsply testtree

ifeq ($(OS), Windows_NT)
CC=cl
CFLAG=
BINS = *.exe *.obj
else
CC=cc
CFLAG=-g
BINS = $(EXES)
endif

all:	$(EXES)

testavl: testavl.c avltree.c prttree.c
	$(CC) $(CFLAG) -o $@ $< avltree.c prttree.c

testrb: testrb.c redblack.c prttree.c
	$(CC) $(CFLAG) -o $@ $< redblack.c prttree.c

testsply:	testsply.c splay.c prttree.c
	$(CC) $(CFLAG) -o $@ $< splay.c prttree.c

testtree:	testtree.c searchtree.c prttree.c
	$(CC) $(CFLAG) -o $@ $< searchtree.c prttree.c

clean:
	rm -f $(BINS)
