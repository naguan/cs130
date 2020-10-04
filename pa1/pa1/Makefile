all: prog1A prog1B

prog1A: main1.o hashTable1.o
		g++ main1.o hashTable1.o -o prog1A

main1.o: main1.cpp
		g++ -std=c++11 -c main1.cpp

HashTable1.o: hashTable1.cpp hashTable1.h
		g++ -std=c++11 -c hashTable1.cpp

prog1B: main2.o hashTable2.o
		g++ main2.o hashTable2.o -o prog1B

main2.o: main2.cpp
		g++ -std=c++11 -c main2.cpp

HashTable2.o: hashTable2.cpp hashTable2.h
		g++ -std=c++11 -c hashTable2.cpp

clean: 
	rm *.o prog1A prog1B

