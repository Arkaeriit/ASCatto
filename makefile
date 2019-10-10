Flags = -Wall -g -Werror
#Flags = -Wall -Werror
NC = -lncurses

all : clean prog

prog : attoLib.o main.o interface.o attoType.o
	gcc main.o attoLib.o interface.o attoType.o $(Flags) $(NC) -o ASCatto

attoLib.o : attoLib.c attoLib.h
	gcc -c attoLib.c $(Flags) -o attoLib.o

attoType.o : attoType.c attoType.h
	gcc -c attoType.c $(Flags) -o attoType.o

main.o : main.c attoLib.h attoInterface.h
	gcc -c main.c  $(Flags) -o main.o

interface.o : attoInterface.h attoInterface.c attoLib.h
	gcc -c attoInterface.c $(Flags) -o interface.o

#progTEST : attoLibTest.o mainTest.o test.o interfaceTest.o
progTEST : attoLibTest.o mainTest.o interfaceTest.o
	#gcc mainTest.o test.o attoLibTest.o interfaceTest.o $(Flags) $(NC) -o ASCattoTest
	gcc mainTest.o attoLibTest.o interfaceTest.o $(Flags) $(NC) -o ASCattoTest

attoLibTest.o : attoLib.c attoLib.h
	gcc -c attoLib.c $(Flags) -o attoLibTest.o

mainTest.o : main.c attoLib.h attoInterface.h
	gcc -c main.c $(Flags) -o mainTest.o

test.o : test.c test.h attoLib.h attoInterface.h
	gcc -c test.c $(Flags) $(NC) -o test.o

interfaceTest.o : attoInterface.h attoInterface.c attoLib.h
	gcc -c attoInterface.c $(Flags) $(NC) -o interfaceTest.o

clean :
	rm -f *.o
	rm -f ASCattoTest
	rm -f ASCatto

test : progTEST
	./ASCattoTest
