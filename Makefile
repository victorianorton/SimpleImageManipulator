prog: main.o filters.o image.o
	g++ -o imageManip main.o filters.o image.o

main3B.o: main.C filters.h image.h
	g++ -c -I. main.C

filters.o: filters.C filters.h image.h
	g++ -c -I. filters.C

image.o: image.C image.h
	g++ -c -I. image.C

clean:
	rm -rf *o $(SOURCES) 