#include <vector>
#include <iostream>
#include <fstream>
#include "Sudoku.h"
#define BLOCKI(a, i) (i / 3 + (int)(a / 3) * 3)
#define BLOCKJ(b, i) (i % 3 + (int)(b / 3) * 3)
using namespace std;

bool duplicate(Sudoku question, int num, int index){
	for(int i = 0; i < 9; ++i){ // check row
		if(num == question.getElement((int)(index / 9) * 9 + i)){
			return true;
		}
	}
	for(int i = 0; i < 9; ++i){ // check column
		if(num == question.getElement((index % 9) + i * 9)){
			return true;
		}
	}
	for(int i = 0; i < 9; ++i){
		int blockI, blockJ;
		blockI = BLOCKI((index / 9), i);
		blockJ = BLOCKJ((index % 9), i);
		if(num == question.getElement(blockI * 9 + blockJ)){
			return true;
		}
	}
	return false;
}

bool solve(Sudoku question, Sudoku &answer){
	int firstZero;
	firstZero = question.getFirstZeroIndex();
	if(firstZero == -1){
		if(question.isCorrect()){
			answer = question;
			return true;
		}else{
			return false;
		}
	}else{
		for(int num = 1; num <= 9; ++num){
			if(duplicate(question, num, firstZero)){
				continue;
			}
			question.setElement(firstZero, num);
			if(solve(question, answer)){
				return true;
			}
		}
		return false;
	}
}

int main(int argc, char **argv){
	Sudoku ques;
	Sudoku ans;
	int num;
	string inputFile = "quiz.txt";
	if(argc == 2){
		inputFile = argv[1];
	}

	ifstream infile(inputFile, ios::in);
	if(!infile.is_open()){
		cerr << "error!Can't open file " << inputFile << endl;
		exit(1);
	}

	for(int i = 0; i < 81; ++i){
		infile >> num;
		ques.setElement(i, num);
	}

	if(solve(ques, ans) == true){
		cout << "Solvable!\n";
		for(int i = 0; i < 81; ++i){
			cout << ans.getElement(i) << " ";
			if(i % 9 == 8){
				cout << endl;
			}
		}
	}else{
		cout << "Unsolvable!!\n";
	}
}
