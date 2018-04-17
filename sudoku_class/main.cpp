#include <iostream>
#include "Sudoku.h"

using namespace std;

int main(int argc, char **argv){
	char temp;
	char quiz[9][9] = {0};
	char *inputFile = "quiz.txt";
	FILE *ifp;
	if(argc == 2){
		inputFile = argv[1];
	}
	ifp = fopen(inputFile, "r");
	if(ifp == NULL){
		fprintf(stderr, "can't open file \"%s\"!!!\n", inputFile);
		exit(1);
	}
	for(int i = 0; i < 9; ++i){//read in
		for(int j = 0; j < 9; ++j){
			fscanf(ifp, "%c", &quiz[i][j]);
			quiz[i][j] -= 48;
		}
		fscanf(ifp, "\n", NULL);
	}
	Sudoku quest(quiz);

	quest.solve();
	quest.printQuiz();

}
