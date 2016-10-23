# makefile de senku
PROG = senku

CC = gcc

CFLAGS = -Wall -Wextra -o

OBJECTS = main.o board.o peg.o matrix.o timer.o score.o

PKG_CONFIG = pkg-config --cflags --libs gtk+-2.0

install: all

all: $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(PROG) $(OBJECTS) $(shell $(PKG_CONFIG))

board.o: board.c board.h matrix.h timer.h score.h
	$(CC) $(CFLAGS) board.o -c board.c $(shell $(PKG_CONFIG))

main.o: main.c board.h matrix.h
	$(CC) $(CFLAGS) main.o -c main.c $(shell $(PKG_CONFIG))

matrix.o: matrix.c matrix.h peg.h
	$(CC) $(CFLAGS) matrix.o -c matrix.c $(shell $(PKG_CONFIG))

peg.o: peg.c peg.h
	$(CC) $(CFLAGS) peg.o -c peg.c $(shell $(PKG_CONFIG))

score.o: score.c score.h
	$(CC) $(CFLAGS) score.o -c score.c $(shell $(PKG_CONFIG))

timer.o: timer.c timer.h
	$(CC) $(CFLAGS) timer.o -c timer.c $(shell $(PKG_CONFIG))

.PHONY: clean
clean:
	rm *.o
