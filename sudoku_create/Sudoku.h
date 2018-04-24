class Sudoku
{
	public:
		Sudoku();
		Sudoku(const char initMap[][9]);
		void setMap(int i, int j, char n);
		char getMap(int i, int j);
		void printMap();
		void takeNote(int a, int b);
		void clearNote(int a, int b);
		bool checkDuplicate(int a, int b, int n);
		int checkSpecial(int a, int b);
		int check(int a, int b);
		bool isCorrect();
		void solve();
		void create(int numberCount = 25);
		void subCreate(int numberCount);
		void clearData();
		void setDif(int dif);
	private:
		char map[9][9] = {0};
		char note[9][9][9] = {0};
		bool initial = true;
};

