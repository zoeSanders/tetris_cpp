all: main

clean: 
	-rm main.o grid.o tetromino.o

main: main.o grid.o tetromino.o
	g++ -g -o main main.o grid.o tetromino.o -lncurses

main.o: main.cpp grid.h  tetromino.h
	g++ -c -g main.cpp

grid.o: grid.cpp grid.h 
	g++ -c -g grid.cpp

tetromino.o: tetromino.cpp tetromino.h
	g++ -c -g tetromino.cpp
