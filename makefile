CC = gcc
CFLAGS = -Wall -ansi -lm -g -std=c99
TARGET = frontEnd
OBJ = main.o parser2.o scanner.o testTree.o

frontEnd: $(OBJ)
	$(CC) $(CFLAGS) -o frontEnd $(OBJ)
main.o : main.c 
	$(CC) $(CFLAGS) -c main.c
parser.o: parser2.c parser.h
	$(CC) $(CFLAGS) -c parser2.c
scanner.o : scanner.c scanner.h
	$(CC) $(CFLAGS) -c scanner.c	
testTree.o : testTree.c testTree.h
	$(CC) $(CFLAGS) -c testTree.c
clean:
	/bin/rm -f *.o $(TARGET)
