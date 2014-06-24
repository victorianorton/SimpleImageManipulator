SRC=main.C image.C sink.C source.C PNMreaderCPP.C PNMwriterCPP.C filters.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o imageManipulator

.C.o: $<
	g++ -I. -c $<

clean:
	rm *.o imageManipulator

