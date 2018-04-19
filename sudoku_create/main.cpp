#include <iostream>
#include "Sudoku.h"

#define RED "\x1B[31m"
#define GRN "\x1B[32m"

int readIn(FILE *ifp, char arr[][9]){
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			fscanf(ifp, "%d", &arr[i][j]);
		}
	}
}

int main(int argc, char **argv){
	int numberCount = 30;
	char quest[9][9] = {{0}};
	bool quizExist = false;
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
					readIn(ifp, quest);
					quizExist = true;
					++i;
				break;
			}
		}
	}

	Sudoku obj(quest);
	if(!quizExist){
		obj.create(numberCount);
	}
	obj.solve();
	printf("Quiz = \n");
	obj.printQuiz();
	printf("\nSol = \n");
	obj.printAns();
}
