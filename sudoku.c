#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char quiz[9][9] = {0};
char note[9][9][9] = {0};
int initial = 1;

int blockCoordinateI(int a, int i){
	return i / 3 + ((int)(a / 3) * 3);
}

int blockCoordinateJ(int b, int i){
	return i % 3 + ((int)(b / 3) * 3);
}

int takeNote(int a, int b){
	if(initial){
		for(int i = 0; i < 9; i++){
			note[a][b][i] = 1;
		}
	}
	for(int i = 0; i < 9; i++){ //check horizontal
		if(quiz[a][i] != 0){
			note[a][b][ quiz[a][i] - 1 ] = 0;
		}
	}
	for(int i = 0; i < 9; i++){ //check vertical
		if(quiz[i][b] != 0){
			note[a][b][ quiz[i][b] - 1 ] = 0;
		}
	}
	for(int i = 0; i < 9; i++){ //check block
		char blockI, blockJ;
		blockI = blockCoordinateI(a, i);
		blockJ = blockCoordinateJ(b, i);
		if(quiz[blockI][blockJ] != 0){
			note[a][b][ quiz[blockI][blockJ] - 1 ] = 0;
		}
	}
}

int clearNote(int a, int b){
	for(int i = 0; i < 9; i++){
		note[a][b][i] = 0;
	}
}

bool checkDuplicate(int a, int b, int n){
	for(int i = 0; i < 9; i++){ //check horizontal
		if(quiz[a][i] == n){
			return true;
		}
	}
	for(int i = 0; i < 9; i++){ //check vertical
		if(quiz[i][b] == n){
			return true;
		}
	}
	for(int i = 0; i < 9; i++){ //check block
		char blockI, blockJ;
		blockI = blockCoordinateI(a, i);
		blockJ = blockCoordinateJ(b, i);
		if(quiz[blockI][blockJ] == n){
			return true;
		}
	}
	return false;
}

int checkSpecial(int a, int b){
	char filled[9] = {0}; //filled means "filled in note"
	for(int i = 0; i < 9; i++){ //check horizontal
		for(int j = 0; j < 9; j++){
			if(note[a][i][j]){
				filled[j]++; //record how many times the number appears
			}
		}
	}
	
	//if a number only appears once in the note, 
	//that means that number is the only one that can fit in the point.
	
	for(int i = 0; i < 9; i++){
		//since the note will only update when "check" processed on the point
		//therefore, we need to check what had filled in
		if(filled[i] == 1 && !checkDuplicate(a, b, i+1)){
			return i + 1;
		}
	}

	for(int i = 0; i < 9; i++){
		filled[i] = 0;
	}
	for(int i = 0; i < 9; i++){ //check vertical
		for(int j = 0; j < 9; j++){
			if(note[i][b][j]){
				filled[j]++; //record how many times the number appears
			}
		}
	}
	for(int i = 0; i < 9; i++){
		if(filled[i] == 1 && !checkDuplicate(a, b, i+1)){
			return i + 1;
		}
	}

	for(int i = 0; i < 9; i++){
		filled[i] = 0;
	}
	for(int i = 0; i < 9; i++){ //check block
		for(int j = 0; j < 9; j++){
			char blockI, blockJ;
			blockI = blockCoordinateI(a, i);
			blockJ = blockCoordinateJ(b, i);
			if(note[blockI][blockJ][j]){
				filled[j]++;
			}
		}
	}
	for(int i = 0; i < 9; i++){
		if(filled[i] == 1 && !checkDuplicate(a, b, i+1)){
			return i + 1;
		}
	}
	return 0;
}

int check(int a, int b){
	int howMany = 0, whatIsIt = 0;
	for(int i = 0; i < 9; i++){
		takeNote(a, b);
		if(note[a][b][i] == 1){ // check how many element are in the note
			howMany++;
			whatIsIt = i;
		}
	}
	if(howMany == 0){
		fprintf(stderr, "error! Can't fill in anything at [%d, %d]\n", a, b);
		return 0;
	}else if(howMany == 1){
		return whatIsIt + 1;
	}

	return initial ? 0 : checkSpecial(a, b);
}

int main(){
	int upDated = 0;
	FILE *ifp;
	ifp = fopen("quiz.txt", "r");
	for(int i = 0; i < 9; i++){//read in
		for(int j = 0; j < 9; j++){
			fscanf(ifp, "%c", &quiz[i][j]);
			quiz[i][j] -= 48;
		}
		fscanf(ifp, "\n", NULL);
	}

	do{
		if(!initial){
			printf("\n=================\n\n");
		}
		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 9; j++){
				printf("%d ", quiz[i][j]);
			}
			printf("\n");
		}

		upDated = 0;
		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 9; j++){
				if(quiz[i][j] == 0){ //only execute where are needed
					quiz[i][j] = check(i, j);
					if(quiz[i][j]){ //if up date success
						upDated++;
						clearNote(i, j);
					}
				}
			}
		}

		initial = 0;
	}while(upDated);
}
