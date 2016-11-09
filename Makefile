# makefile de senku
PROG = senku

CC = gcc

CFLAGS = -Wall -Wextra -o

OBJECTS = main.o board.o peg.o matrix.o timer.o score.o memento.o

install: all

all: $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(PROG) $(OBJECTS)

board.o: board.c board.h matrix.h timer.h score.h
	$(CC) $(CFLAGS) board.o -c board.c

main.o: main.c board.h matrix.h
	$(CC) $(CFLAGS) main.o -c main.c

matrix.o: matrix.c matrix.h peg.h
	$(CC) $(CFLAGS) matrix.o -c matrix.c

peg.o: peg.c peg.h
	$(CC) $(CFLAGS) peg.o -c peg.c

score.o: score.c score.h
	$(CC) $(CFLAGS) score.o -c score.c

timer.o: timer.c timer.h
	$(CC) $(CFLAGS) timer.o -c timer.c

memento.o: memento.c memento.h
	$(CC) $(CFLAGS) memento.o -c memento.c
	
.PHONY: clean
clean:
	rm *.o
