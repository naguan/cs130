all: prog2

prog2: main.o splayTree.o
		g++ main.o splayTree.o -o prog2

main.o: main.cpp
		g++ -std=c++11 -c main.cpp

splayTree.o: splayTree.cpp splayTree.h
		g++ -std=c++11 -c splayTree.cpp

clean: 
	rm *.o prog2

