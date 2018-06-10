#ifndef BIGGAME_H
#define BIGGAME_H

#include <utility>
#include "include/game.h"
#include <cstring>
#include <string>

class BigGame {

private:
	std::pair<int, int> setGame(int i, int j);
	bool validPos(std::pair<int, int> g, std::pair<int, int> p);
	
public:
	Game tab[3][3];
	std::pair<int, int> curGame;

	BigGame();
	int checkWin();
	bool checkFull();
	bool markPos(std::pair<int, int> g, std::pair<int, int> p, int player);
	std::string completeGame();
	std::string toString();
	int getCurPos();
};


#endif
