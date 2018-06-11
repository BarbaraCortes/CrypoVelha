#include "include/game.h"

Game::Game() {
	// o game comeca zerado
	memset(mat, 0, sizeof(mat)); 
}

int Game::checkWin() {
	// checa se ganhou por alguma linha
	for (int i = 0; i < 3; i++) {
		if (mat[i][0] && mat[i][0] == mat[i][1] && mat[i][0] == mat[i][2]) return mat[i][0];
	}

	// checa se ganhou por alguma coluna
	for (int j = 0; j < 3; j++) {
		if (mat[0][j] && mat[0][j] == mat[1][j] && mat[0][j] == mat[2][j]) return mat[0][j];
	}

	// checa se ganhou por alguma diagonal
	if (mat[0][0] && mat[0][0] == mat[1][1] && mat[0][0] == mat[2][2]) return mat[0][0];
	if (mat[0][2] && mat[0][2] == mat[1][1] && mat[0][2] == mat[2][0]) return mat[0][2];

	// ninguem ganhou ainda
	return 0;
}

bool Game::checkFull() {
	if (checkWin()) return true;
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// ainda ha posicao a ser marcada
			if (mat[i][j] == 0) return false;
		}
	}
	
	// tabuleiro cheio
	return true;
}

bool Game::validPos(int i, int j) {
	// posicao a ser marcada deve estar vazia
	return (mat[i][j] == 0);
}

std::string Game::toString() {
	std::string res;
	
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			res += '0' + mat[i][j];
		}
	}
	
	return res;
}
