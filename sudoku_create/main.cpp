#include <iostream>
#include "Sudoku.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

int main(int argc, char **argv){
	Sudoku quiz;

	if(argc > 1){
		quiz.create(atoi(argv[1]));
	}else{
		quiz.create();
	}
	printf("Quiz = \n");
	quiz.printQuiz();
	printf("\nSol = \n");
	quiz.solve();
	quiz.printQuiz();
}
