Flags = -Wall -g -Werror

all : prog

prog : attoLib.o main.o test.o
	gcc main.o test.o attoLib.o $(Flags) -o prgMk

attoLib.o : attoLib.c attoLib.h
	gcc -c attoLib.c $(Flags) -o attoLib.o

main.o : main.c attoLib.h test.h
	gcc -c main.c $(Flags) -o main.o

test.o : test.c test.h
	gcc -c test.c $(Flags) -o test.o

clean :
	rm -f *.o
	rm -f prgMK

test : clean all
	./prgMk
