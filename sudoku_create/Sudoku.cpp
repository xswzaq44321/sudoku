#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include "sudoku.h"
#define BLOCKI(a, i) (i / 3 + static_cast<int>(a / 3) * 3)
#define BLOCKJ(b, i) (i % 3 + static_cast<int>(b / 3) * 3)
#define GRN   "\x1B[32m"
#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"

Sudoku::Sudoku(){
}

Sudoku::Sudoku(const char initMap[][9]){
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			quiz[i][j] = initMap[i][j];
		}
	}
}

void Sudoku::setQuiz(int i, int j, char n){
	quiz[i][j] = n;
}

char Sudoku::getQuiz(int i, int j){
	return quiz[i][j];
}

void Sudoku::printQuiz(){
	printf("=====================\n");
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			printf(quiz[i][j] ? GRN "%d " RESET : "%d ", quiz[i][j]);
			printf(j % 3 == 2 ? "|" : "");
		}
		printf(i % 3 == 2 ? "\n---------------------\n" :"\n");
	}
	printf("=====================\n");
}

void Sudoku::printAns(){
	printf("=====================\n");
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			if(ans[i][j]){
				if(ans[i][j] == quiz[i][j]){
					printf(GRN "%d " RESET, ans[i][j]);
				}else{
					printf(CYN "%d " RESET, ans[i][j]);
				}
			}else{
				printf("%d ", ans[i][j]);
			}
			printf(j % 3 == 2 ? "|" : "");
		}
		printf(i % 3 == 2 ? "\n---------------------\n" :"\n");
	}
	printf("=====================\n");
}

void Sudoku::takeNote(int a, int b){
	if(initial){
		for(int i = 0; i < 9; ++i){
			note[a][b][i] = 1;
		}
	}
	for(int i = 0; i < 9; ++i){ // check row
		if(ans[a][i] != 0){
			note[a][b][ ans[a][i] - 1 ] = 0;
		}
	}
	for(int i = 0; i < 9; ++i){ // check column
		if(ans[i][b] != 0){
			note[a][b][ ans[i][b] - 1 ] = 0;
		}
	}
	for(int i = 0; i < 9; ++i){ // check block
		char blockI, blockJ;
		blockI = BLOCKI(a, i);
		blockJ = BLOCKJ(b, i);
		if(ans[blockI][blockJ] != 0){
			note[a][b][ ans[blockI][blockJ] - 1 ] = 0;
		}
	}
}

void Sudoku::clearNote(int a, int b){
	for(int i = 0; i < 9; ++i){
		note[a][b][i] = 0;
	}
}

bool Sudoku::checkDuplicate(int a, int b, int n, char arr[][9]){
	char blockI, blockJ;
	for(int i = 0; i < 9; ++i){ // check row
		if(i != b && arr[a][i] == n){
			return true;
		}
	}
	for(int i = 0; i < 9; ++i){ // check column
		if(i != a && arr[i][b] == n){
			return true;
		}
	}
	for(int i = 0; i < 9; ++i){ // check block
		blockI = BLOCKI(a, i);
		blockJ = BLOCKJ(b, i);
		if((blockI != a && blockJ != b) && arr[blockI][blockJ] == n){
			return true;
		}
	}
	return false;
}

int Sudoku::checkSpecial(int a, int b){
	char filled[9] = {0}; //"filled" is used to record how many time a number appears in the "notes of row, column, block"

	for(int i = 0; i < 9; ++i){ //check row
		for(int j = 0; j < 9; ++j){
			if(note[a][i][j]){
				filled[j]++; //record how many times the number appears
			}
		}
	}
	for(int i = 0; i < 9; ++i){
		//if a number only appears once in the "note of the row, column, block",
		//that means that number is the only one that can fit in the point.
		//since the note of the point will only update when "check()" processed
		//therefore, we need to check what had filled in before
		if(filled[i] == 1 && !checkDuplicate(a, b, i+1, ans)){
			return i + 1;
		}
	}

	for(int i = 0; i < 9; ++i){
		filled[i] = 0;
	}
	for(int i = 0; i < 9; ++i){ //check column
		for(int j = 0; j < 9; ++j){
			if(note[i][b][j]){
				filled[j]++; //record how many times the number appears
			}
		}
	}
	for(int i = 0; i < 9; ++i){
		if(filled[i] == 1 && !checkDuplicate(a, b, i+1, ans)){
			return i + 1;
		}
	}

	for(int i = 0; i < 9; ++i){
		filled[i] = 0;
	}
	for(int i = 0; i < 9; ++i){ //check block
		for(int j = 0; j < 9; ++j){
			char blockI, blockJ;
			blockI = BLOCKI(a, i);
			blockJ = BLOCKJ(b, i);
			if(note[blockI][blockJ][j]){
				filled[j]++;
			}
		}
	}
	for(int i = 0; i < 9; ++i){
		if(filled[i] == 1 && !checkDuplicate(a, b, i+1, ans)){
			return i + 1;
		}
	}
	return 0;
}

int Sudoku::check(int a, int b){
	int howMany = 0, whatIsIt = 0;
	for(int i = 0; i < 9; ++i){
		takeNote(a, b);
		if(note[a][b][i] == 1){ // check how many element are in the note
			howMany++;
			whatIsIt = i;
		}
	}
	if(howMany == 0){
		fprintf(stderr, "error! Can't fill any number on [%d, %d]\n", a, b);
		return 0;
	}else if(howMany == 1){
		return whatIsIt + 1;
	}

	return initial ? 0 : checkSpecial(a, b);
}

void Sudoku::solve(){
	int upDate;
	initial = true;
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			ans[i][j] = quiz[i][j];
		}
	}
	do{
		upDate = 0;
		for(int i = 0; i < 9; ++i){
			for(int j = 0; j < 9; ++j){
				if(ans[i][j] == 0){ // only execute where are needed
					ans[i][j] = check(i, j);
					if(ans[i][j] != 0){ // if up date success
						++upDate;
						clearNote(i, j);
					}
				}
			}
		}
		initial = false;
	}while(upDate);
}

bool Sudoku::isCorrect(char arr[][9]){
	bool checkResult;
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			if((arr[i][j] == 0) || checkDuplicate(i, j, arr[i][j], arr)){
				return false;
			}
		}
	}
	return true;
}

void Sudoku::clearMember(){
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			quiz[i][j] = 0;
			ans[i][j] = 0;
			clearNote(i, j);
			initial = true;
		}
	}
}

void Sudoku::subCreate(int numberCount){
	char temp, tempI, tempJ, count = 0;
	while(count < numberCount){
		temp = rand() % 9 + 1;
		tempI = rand() % 9;
		tempJ = rand() % 9;
		if(quiz[tempI][tempJ] == 0 && !checkDuplicate(tempI, tempJ, temp, quiz)){
			quiz[tempI][tempJ] = temp;
			++count;
		}
	}
}

void Sudoku::create(int numberCount){
	Sudoku temp;
	srand(time(NULL));
	bool result = false;
	while(!result){
		clearMember();
		subCreate(numberCount);
		//printf("\n\n");
		//temp.printQuiz();
		solve();
		//temp.printQuiz();
		result = isCorrect(ans);
	}
}

void setDif(int dif){
	for(int i = 0; i < dif; ++i){
		
	}
}
