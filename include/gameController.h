#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include "include/bigGame.h"
#include <sstream>
#include <string>


class GameController {
public:
	int turn;
	BigGame *b;

	GameController();
	int userInput(std::string msg, int player);
	std::string getBoardPackage();
	std::string getBigGamePackage();
	std::string getControlPackage(int toPlayer);

};

#endif
