#ifndef GAME_H
#define GAME_H

#include <cstring> 
#include <string>

class Game {
public:
	int mat[3][3];
	Game();
	int checkWin();
	bool checkFull();
	bool validPos(int i, int j);
	std::string toString();
};

#endif
