#include "include/game.h"

Game::Game() {
	memset(mat, 0, sizeof(mat));
}

int Game::checkWin() {
	for (int i = 0; i < 3; i++) {
		if (mat[i][0] && mat[i][0] == mat[i][1] && mat[i][0] == mat[i][2]) return mat[i][0];
	}

	for (int j = 0; j < 3; j++) {
		if (mat[0][j] && mat[0][j] == mat[1][j] && mat[0][j] == mat[2][j]) return mat[0][j];
	}

	if (mat[0][0] && mat[0][0] == mat[1][1] && mat[0][0] == mat[2][2]) return mat[0][0];
	if (mat[0][2] && mat[0][2] == mat[1][1] && mat[0][2] == mat[2][0]) return mat[0][2];

	return 0;
}

bool Game::checkFull() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (mat[i][j] == 0) return false;
		}
	}
	
	return true;
}

bool Game::validPos(int i, int j) {
	return (mat[i][j] == 0);
}

std::string Game::toString() {
	std::string res;
	
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			res += mat[i][j];
		}
	}
	
	return res;
}
