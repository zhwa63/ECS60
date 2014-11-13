router.out : router.o TripsRunner.o vertex.o
	g++ -ansi -Wall -g -o router.out router.o TripsRunner.o vertex.o 

router.o : router.cpp TripsRunner.h router.h vertex.h 
	g++ -ansi -Wall -g -c router.cpp

vertex.o : vertex.cpp vertex.h TripsRunner.h router.h
	g++ -ansi -Wall -g -c vertex.cpp

TripsRunner.o : TripsRunner.cpp TripsRunner.h router.h CPUTimer.h 
	g++ -ansi -Wall -g -c TripsRunner.cpp

clean : 
	rm -f router.out router.o  TripsRunner.o vertex.o
