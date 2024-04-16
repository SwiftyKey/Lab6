#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class TicTacToe {
private:
	int fieldSize = 3;
	char firstPlayer = 'x';
	char nextPlayer = firstPlayer;
	bool endGame = false;
	vector<vector<char>> field;

	void fillField() {
		field.clear();
		field.resize(fieldSize, vector<char>(fieldSize, '.'));
	}

	bool checkDraw() const {
		bool flagDraw = true;

		for (auto& row : field)
			for (auto& col : row)
				if (col == '.') {
					flagDraw = false;
					break;
				}

		return flagDraw;
	}

	bool checkDiagonal() const {
		bool flagWin = true;

		for (int i = 1; i < fieldSize; i++) {
			if (field[i][i] != field[i - 1][i - 1] || field[i][i] == '.') {
				flagWin = false;
				break;
			}
		}

		return flagWin;
	}

	bool checkSideDiagonal() const {
		bool flagWin = true;

		for (int i = 1; i < fieldSize; i++) {
			if (field[i][fieldSize - i - 1] != field[i - 1][fieldSize - i] || field[i][fieldSize - i - 1] == '.') {
				flagWin = false;
				break;
			}
		}

		return flagWin;
	}

	bool checkRows() const {
		bool flagWin;
		for (int i = 0; i < fieldSize; i++) {
		    flagWin = false;
			for (int j = 1; j < fieldSize; j++) {
				if (field[i][j] == field[i][j - 1] && field[i][j] != '.')
					flagWin = true;
				else {
				    flagWin = false;
				    break;
				}
			}
			if (flagWin) break;
		}

		return flagWin;
	}

	bool checkCols() const {
		bool flagWin;

		for (int i = 0; i < fieldSize; i++) {
		    flagWin = false;
			for (int j = 1; j < fieldSize; j++) {
				if (field[j][i] == field[j - 1][i] && field[j][i] != '.')
					flagWin = true;
				else {
				    flagWin = false;
					break;
				}
			}
			if (flagWin) break;
		}

		return flagWin;
	}

	void checkEndGame() {
		if (checkRows() || checkCols() || checkDiagonal() || checkSideDiagonal()) {
			char winner = nextPlayer;
			if (winner == 'x') winner = 'X';
			cout << "Победитель - " << winner << endl;
			endGame = true;
		}
		else if (checkDraw()) {
			cout << "Ничья" << endl;
			endGame = true;
		}
	}
public:
	TicTacToe(char player='x') {
		fillField();

		if (player == '0') {
			firstPlayer = player;
			nextPlayer = firstPlayer;
		}
	}

	void show_table() const {
		for (auto& row : field) {
			for (auto& col : row) cout << col;
			cout << endl;
		}
	}

	void restart() {
		fillField();
		endGame = false;
		nextPlayer = firstPlayer;
	}

	void make_to_move(int row, int col) {
		if (!endGame && row >= 1 && row <= fieldSize &&
			col >= 1 && col <= fieldSize && field[row - 1][col - 1] == '.') {
			field[row - 1][col - 1] = nextPlayer;
			checkEndGame();
			nextPlayer = (nextPlayer == 'x') ? '0' : 'x';
		}
		else {
			cout << "Ход не может быть выполнен" << endl;
		}
	}
};
