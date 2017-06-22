
EXES= closest huffman tictactoe turnpike

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

closest: closest.c msort.c
	$(CC) $(CFLAG) -o $@ $< msort.c

huffman:	huffman.c hufftree.c binheap.c prttree.c
	$(CC) $(CFLAG) -o $@ $< hufftree.c binheap.c prttree.c

tictactoe:	tictactoe.c
	$(CC) $(CFLAG) -o $@ $<

turnpike:	turnpike.c searchtree.c prttree.c
	$(CC) $(CFLAG) -o $@ $< searchtree.c prttree.c

clean:
	rm -f $(BINS)
