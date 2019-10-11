#Flags = -Wall -g -Werror
Flags = -Wall -Werror
NC = -lncurses

all : clean prog

prog : attoLib.o main.o interface.o attoType.o
	gcc main.o attoLib.o interface.o attoType.o $(NC) -o ASCatto

attoLib.o : attoLib.c attoLib.h
	gcc -c attoLib.c $(Flags) -o attoLib.o

attoType.o : attoType.c attoType.h
	gcc -c attoType.c $(Flags) -o attoType.o

main.o : main.c attoLib.h attoInterface.h
	gcc -c main.c  $(Flags) -o main.o

interface.o : attoInterface.h attoInterface.c attoLib.h
	gcc -c attoInterface.c $(Flags) -o interface.o

clean :
	rm -f *.o
	rm -f ASCatto

install : 
	cp -f ASCatto /usr/local/bin

unistall :
	rm -f /usr/local/bin/ASCatto

