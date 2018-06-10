#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "include/gameboard.h"
#include "include/label.h"

class Protocol {
protected:
	GameBoard *gameBoard;
	Label *statusLabel;
	
	std::string board, bigGame;
	
	void parseBoard(std::string msg);
	void parseBigGame(std::string msg);
	void parseControl(std::string msg);
	void parseError(std::string msg);

public:
	Protocol(GameBoard *gameBoard, Label *statusLabel);

	void parsePacket(std::string msg);	
};

#endif
