#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

class GameController(){
public:
	int turn;
	BigGame *b;

	int userInput(string msg, int player);
	std::string getBoardPackage();
	std::string getBigGamePackage();
	std::string getControlPackage();

};

#ifndef
