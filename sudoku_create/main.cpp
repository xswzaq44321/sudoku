#include <iostream>
#include "Sudoku.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

int main(int argc, char **argv){
	Sudoku quiz;
	int numberCount = 30;
	FILE *ifp;

	for(int i = 1; i < argc; ++i){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'n':
					numberCount = atoi(argv[i + 1]);
					++i;
				break;
				case 'f':
					ifp = fopen(argv[i + 1], "r");
					++i;
				break;
				default:
				break;
			}
		}
	}

	quiz.create(numberCount);
	printf("Quiz = \n");
	quiz.printQuiz();
	printf("\nSol = \n");
	quiz.solve();
	quiz.printQuiz();
}
