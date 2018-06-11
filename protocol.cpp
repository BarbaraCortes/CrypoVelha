#include <cassert>
#include <iostream>

#include "include/protocol.h"

Protocol::Protocol(GameBoard *gameBoard, Label *statusLabel)
 : gameBoard(gameBoard), statusLabel(statusLabel)
{
	
}

void Protocol::parsePacket(std::string msg) {
	assert(msg.size());
	switch (msg[0]) {
		case 'T': return parseBoard(msg.substr(1));
		case 'B': return parseBigGame(msg.substr(1));
		case 'C': return parseControl(msg.substr(1));
		case 'E': return parseError(msg.substr(1));
		default:
			std::cerr << "Pacote de tipo desconhecido: " << msg[0] << std::endl;
			return;
	}
}

void Protocol::parseBoard(std::string msg) {
	board = msg;
	if (bigGame.size()) {
		gameBoard->setBoard(Board(board, bigGame));
	}
}

void Protocol::parseBigGame(std::string msg) {
	bigGame = msg;
	if (board.size()) {
		gameBoard->setBoard(Board(board, bigGame));
	}
}

void Protocol::parseControl(std::string msg) {
	int pos = msg[0] - '0';
	int state = msg[1] - '0';
	if (pos == 9) {
		gameBoard->setSelectedBlock(-1, -1);
	} else {
		gameBoard->setSelectedBlock(pos / 3, pos % 3);
	}
	switch (state) {
		case 0:
			if (pos != 9) statusLabel->setText("Status: sua vez de jogar");
			else statusLabel->setText("Status: vez do oponente");
			break;
		case 1:
			statusLabel->setText("Voce perdeu :(");
			break;
		case 2:
			statusLabel->setText("Voce ganhou!!!");
			break;
		case 3:
			statusLabel->setText("Deu velha :/");
			break;
	}
}

void Protocol::parseError(std::string msg) {

}

