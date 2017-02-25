# makefile de senku
PROG = senku

CC = gcc 

CFLAGS = -O3 -Wall -Wextra -o

LDFLAGS = -mwindows

OBJECTS = main.o board.o peg.o matrix.o timer.o score.o memento.o xfile.o

PKG_CONFIG = `C:/GTK/bin/pkg-config --cflags --libs gtk+-3.0`

XML = `C:/GTK/bin/pkg-config --cflags --libs libxml-2.0`

install: all

all: $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(PROG) $(OBJECTS) $(PKG_CONFIG) $(XML) $(LDFLAGS) 

board.o: board.c board.h matrix.h timer.h score.h peg.h memento.h
	$(CC) $(CFLAGS) board.o -c board.c $(PKG_CONFIG)

main.o: main.c board.h matrix.h peg.h memento.h
	$(CC) $(CFLAGS) main.o -c main.c $(PKG_CONFIG) 

matrix.o: matrix.c matrix.h peg.h memento.h xfile.h
	$(CC) $(CFLAGS) matrix.o -c matrix.c $(PKG_CONFIG) 

peg.o: peg.c peg.h
	$(CC) $(CFLAGS) peg.o -c peg.c 

score.o: score.c score.h
	$(CC) $(CFLAGS) score.o -c score.c 

timer.o: timer.c timer.h
	$(CC) $(CFLAGS) timer.o -c timer.c 

memento.o: memento.c memento.h peg.h matrix.h
	$(CC) $(CFLAGS) memento.o -c memento.c 

xfile.o: xfile.c xfile.h 
	$(CC) $(CFLAGS) xfile.o -c xfile.c $(XML)

.PHONY: clean
clean:
	rm *.o
