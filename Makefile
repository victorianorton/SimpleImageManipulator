prog: main.o functions.o image.o
	g++ -o imageManipulator main.o functions.o image.o

main3B.o: main.C functions.h image.h
	g++ -c -I. main.C

functions.o: functions.C functions.h image.h
	g++ -c -I. functions.C

image.o: image.C image.h
	g++ -c -I. image.C

clean:
	rm -rf *o $(SOURCES) 
