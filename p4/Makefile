encoder.out : decoder.o encoder.o encoderRunner.o HuffNode.o
	g++ -ansi -Wall -g -o encoder.out decoder.o encoder.o HuffNode.o encoderRunner.o

decoder.o : decoder.cpp decoder.h BinaryHeap.h
	g++ -ansi -Wall -g -c decoder.cpp

encoder.o : encoder.cpp encoder.h BinaryHeap.h 
	g++ -ansi -Wall -g -c encoder.cpp

HuffNode.o : HuffNode.h
	g++ -ansi -Wall -g -c HuffNode.cpp
	
encoderRunner.o : encoderRunner.cpp CPUTimer.h encoder.h decoder.h 
	g++ -ansi -Wall -g -c encoderRunner.cpp

clean : 
	rm -f encoder.out decoder.o encoder.o encoderRunner.o
