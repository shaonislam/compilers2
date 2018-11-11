CC = gcc
CFLAGS = -Wall -ansi -lm
TARGET = frontEnd
OBJ = main.o parser.o scanner.o

frontEnd: $(OBJ)
	$(CC) $(CFLAGS) -o frontEnd $(OBJ)
main.o : main.c 
	$(CC) $(CFLAGS) -c main.c
parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c
scanner.o : scanner.c scanner.h
	$(CC) $(CFLAGS) -c scanner.c	
clean:
	/bin/rm -f *.o $(TARGET)
