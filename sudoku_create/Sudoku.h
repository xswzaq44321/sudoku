class Sudoku
{
	public:
		Sudoku();
		Sudoku(const char initMap[][9]);
		void setQuiz(int i, int j, char n);
		char getQuiz(int i, int j);
		void printQuiz();
		void printAns();
		void takeNote(int a, int b);
		void clearNote(int a, int b);
		bool checkDuplicate(int a, int b, int n, char arr[][9]);
		int checkSpecial(int a, int b);
		int check(int a, int b);
		void solve();
		bool isCorrect(char arr[][9]);
		void clearMember();
		void subCreate(int numberCount);
		void create(int numberCount = 30);
		void setDif(int dif);
	private:
		char quiz[9][9] = {0};
		char ans[9][9] = {0};
		char note[9][9][9] = {0};
		bool initial = true;
};

