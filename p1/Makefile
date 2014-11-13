#Variables
CC=g++
CFlags= -Wall -g -W

all: puzzle.o main.o
	$(CC) $(CFlags) puzzle.o main.o -o solver.out

puzzle.o:
	$(CC) -g -c puzzle.h puzzle.cpp

main.o:
	$(CC) -g -c main.cpp

clean:
	rm -rf *.o
