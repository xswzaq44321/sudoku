#include <iostream>
#include <vector>

class Sudoku{
	public:
		Sudoku();
		Sudoku(const int init_map[]);
		void setMap(const int set_map[]);
		int getElement(int index);
		void setElement(int index, int value);
		int getFirstZeroIndex();
		bool isCorrect();
		static const int sudokuSize = 81;

	private:
		bool checkUnity(int arr[]);
		int map[sudokuSize];
};
