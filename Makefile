
CC=gcc
CFLAGS=-c
CFLAGS2=-o
SOURCES=proj3A.c

lib:
	$(CC) $(CFLAGS) $(SOURCES)
	$(CC) proj3A.o $(CFLAGS2) proj3A

clean:
	rm -rf *o $(SOURCES) 
