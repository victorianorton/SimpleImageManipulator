CC=gcc
CFLAGS=-c
CFLAGS2=-o
SOURCES=imageManip.c

lib:
	$(CC) $(CFLAGS) $(SOURCES)
	$(CC) imageManip.o $(CFLAGS2) imageManip

clean:
	rm -rf *o $(SOURCES) 