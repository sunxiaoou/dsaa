
EXES= critpath dijkstra eulercir findart prim topsort unweigh

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

critpath:	critpath.c graph.c linkque.c
	$(CC) $(CFLAG) -o $@ $< graph.c linkque.c

dijkstra:	dijkstra.c graph.c linkque.c
	$(CC) $(CFLAG) -o $@ $< graph.c linkque.c

eulercir:	eulercir.c graph.c linkque.c
	$(CC) $(CFLAG) -o $@ $< graph.c linkque.c

findart:	findart.c graph.c linkque.c
	$(CC) $(CFLAG) -o $@ $< graph.c linkque.c

prim:	prim.c graph.c linkque.c
	$(CC) $(CFLAG) -o $@ $< graph.c linkque.c

topsort:	topsort.c
	$(CC) $(CFLAG) -o $@ $<

unweigh:	unweigh.c
	$(CC) $(CFLAG) -o $@ $<


clean:
	rm -f $(BINS)
