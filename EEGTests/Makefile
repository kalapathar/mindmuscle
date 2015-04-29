main: ThinkGearStreamParser.o main.o
	g++ -o main main.o ThinkGearStreamParser.o

main.o: main.cpp
	g++ -g -Wall -std=c++11 -c main.cpp


ThinkGearStreamParser.o: ThinkGearStreamParser.c ThinkGearStreamParser.h
	gcc -c ThinkGearStreamParser.c