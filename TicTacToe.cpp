#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class TicTacToe {
private:
	int fieldSize = 3;

	char firstPlayer = 'X';
	char currentPlayer = firstPlayer;

	bool endGame = false;

	vector<vector<char>> field;

	void fillField() {
		field.clear();
		field.resize(fieldSize, vector<char>(fieldSize, '.'));
	}

	bool checkDraw() const {
		for (auto& row : field) {
			for (auto& col : row) {
				if (col == '.') {
					return false;
				}
			}
		}

		return true;
	}

	bool checkDiagonal() const {
		for (int i = 1; i < fieldSize; i++) {
			if (field[i][i] != field[i - 1][i - 1] || cellIsFree(i, i)) {
				return false;
			}
		}

		return true;
	}

	bool checkSideDiagonal() const {
		for (int i = 1; i < fieldSize; i++) {
			if (field[i][fieldSize - i - 1] != field[i - 1][fieldSize - i] || cellIsFree(i, fieldSize - i - 1)) {
				return false;
			}
		}

		return true;
	}

	bool checkRows() const {
		for (auto& row: field) {
			if (count(row.begin(), row.end(), currentPlayer) == fieldSize) {
				return true;
			}
		}

		return false;
	}

	bool checkCols() const {
		for (int i = 0; i < fieldSize; i++) {
			for (int j = 0; j < fieldSize; j++) {
				if (field[j][i] - currentPlayer != 0) {
					return false;
				}
			}
		}

		return true;
	}

	void checkEndGame() {
		if (checkRows() || checkCols() || checkDiagonal() || checkSideDiagonal()) {
			cout << "Победитель - " << currentPlayer << endl;
			endGame = true;
		}
		else if (checkDraw()) {
			cout << "Ничья" << endl;
			endGame = true;
		}
	}

	bool cellIsFree(int row, int col) const {
		return field[row - 1][col - 1] == '.';
	}

	bool coordIsIn(int coord) const {
		return coord >= 1 && coord <= fieldSize;
	}

	bool checkCoords(int row, int col) const {
		return coordIsIn(row) && coordIsIn(col);
	}

	void changedPlayer() {
		currentPlayer = (currentPlayer == 'X') ? '0' : 'X';
	}
public:
	TicTacToe(int size=3, char player='X') {
		fieldSize = size;

		fillField();

		if (player == '0') {
			firstPlayer = player;
			currentPlayer = firstPlayer;
		}
	}

	void showTable() const {
		for (auto& row : field) {
			for (auto& col : row) {
				cout << col;
			}
			cout << endl;
		}
	}

	void restart() {
		fillField();
		endGame = false;
		currentPlayer = firstPlayer;
	}

	void makeToMove(int row, int col) {
		if (endGame) {
			cout << "Игра завершена" << endl;
		}
		else if (checkCoords(row, col) && cellIsFree(row, col)) {
			field[row - 1][col - 1] = currentPlayer;

			checkEndGame();
			changedPlayer();
		}
		else {
			cout << "Ход не может быть выполнен" << endl;
		}
	}
};
