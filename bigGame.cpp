#include "include/bigGame.h"
#include <time.h>

BigGame::BigGame() {
	srand(time(NULL));
	curGame = std::make_pair(rand()%8, rand()%8);
}

int BigGame::checkWin() {
	for (int i = 0; i < 3; i++) {
		if (tab[i][0].checkWin() && tab[i][0].checkWin() == tab[i][1].checkWin() && tab[i][0].checkWin() == tab[i][2].checkWin()) 
			return tab[i][0].checkWin();
	}

	for (int j = 0; j < 3; j++) {
		if (tab[0][j].checkWin() && tab[0][j].checkWin() == tab[1][j].checkWin() && tab[0][j].checkWin() == tab[2][j].checkWin()) 
			return tab[0][j].checkWin();
	}

	if (tab[0][0].checkWin() && tab[0][0].checkWin() == tab[1][1].checkWin() && tab[0][0].checkWin() == tab[2][2].checkWin()) 
		return tab[0][0].checkWin();
	
	if (tab[0][2].checkWin() && tab[0][2].checkWin() == tab[1][1].checkWin() && tab[0][2].checkWin() == tab[2][0].checkWin()) 
		return tab[0][2].checkWin();

	return 0;
}

bool BigGame::checkFull() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!tab[i][j].checkWin() && !tab[i][j].checkFull()) return false; 
		}
	}
	
	return true;
}

bool BigGame::validPos(std::pair<int, int> g, std::pair<int, int> p) {
	return (g == curGame && tab[g.first][g.second].validPos(p.first, p.second));
}

std::pair<int, int> BigGame::setGame(int i, int j) {
	while (tab[i][j].checkWin() || tab[i][j].checkFull()) {
		j++;
		if (j == 3) {
			i++;
			j = 0;
		}
		if (i == 3) {
			i = 0;
			j = 0;
		}
	}
	return std::make_pair(i, j);
}

bool BigGame::markPos(std::pair<int, int> g, std::pair<int, int> p, int player) {
	if (!validPos(g, p)) return false;
	
	tab[g.first][g.second].mat[p.first][p.second] = player;
	
	curGame = setGame(p.first, p.second);
	return true;
}

std::string BigGame::completeGame() {
	std::string res;
	
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			res += '0' + tab[i][j].toString();
		}
	}
	
	return res;
}

std::string BigGame::toString() {
	std::string res;
	
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			res += '0' + tab[i][j].checkWin();
		}
	}
	
	return res;
}

int BigGame::getCurPos() {
	return curGame.first * 3 + curGame.second;
}
