
CC=gcc
CFLAGS=-c
CFLAGS2=-o
SOURCES=proj3A.c

lib:
	$(CC) $(CFLAGS) $(SOURCES)
	$(CC) proj3A.o $(CFLAGS2) proj3A
	./proj3A 3A_input.pnm 3A_output.pnm

clean:
	rm -rf *o $(SOURCES) 