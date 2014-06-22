#SRC=CFiles/main.C CFiles/image.C CFiles/sink.C CFiles/source.C CFiles/PNMreader.C CFiles/PNMwriter.C CFiles/filters.C
#EXT=CFiles/
SRC=main.C image.C sink.C source.C PNMreader.C PNMwriter.C filters.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o imageManipulator

.C.o: $<
	g++ -I. -c $<

clean:
	rm *.o imageManipulator

