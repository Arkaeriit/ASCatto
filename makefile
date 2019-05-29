Flags = -Wall -g -Werror
NC = -lncurses

all : prog

prog : attoLib.o main.o test.o interface.o
	gcc main.o test.o attoLib.o interface.o $(Flags) $(NC) -o ASCattoTest

attoLib.o : attoLib.c attoLib.h
	gcc -c attoLib.c $(Flags) -o attoLib.o

main.o : main.c attoLib.h test.h
	gcc -c main.c $(Flags) -o main.o

test.o : test.c test.h attoLib.h attoInterface.h
	gcc -c test.c $(Flags) $(NC) -o test.o

interface.o : attoInterface.h attoInterface.c attoLib.h
	gcc -c attoInterface.c $(Flags) $(NC) -o interface.o
clean :
	rm -f *.o
	rm -f prgMK

test : clean all
	./ASCattoTest
