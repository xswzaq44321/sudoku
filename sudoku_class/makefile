solver: main.o Sudoku.o
	g++ -o solver main.o Sudoku.o
main.o: main.cpp Sudoku.h
	g++ -c main.cpp
Sudoku.o: Sudoku.h Sudoku.cpp
	g++ -c Sudoku.cpp
clear:
	rm *.o
