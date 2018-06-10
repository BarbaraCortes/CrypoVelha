#include "include/gameController.h"
#include <assert.h>

enum{
	NADA = '0',
	PERDEU,
	GANHOU,
	VELHA
};

GameController::GameController(){
	b = new BigGame();
	turn = 1;
}

int GameController::userInput(std::string msg, int player){
	if(turn != player) return -1; //Não é sua vez

	assert(msg.size() == 4);

	std::pair<int, int> g, p;
	std::stringstream ss(msg);

	char x, y;
	ss >> x;
	ss >> y;
	g = std::make_pair((int)(x-'0'), (int)(y-'0'));

	ss >> x;
	ss >> y;
	p = std::make_pair((int)(x-'0'), (int)(y-'0'));

	if(!b->markPos(g, p, player)) return 1; //Posicao invalida

	turn = 3 - turn;
	
	return 0; //Sem error
}

std::string GameController::getBoardPackage(){
	return 'T' + b->completeGame();
}

std::string GameController::getBigGamePackage(){
	return 'B' + b->toString();
}

std::string GameController::getControlPackage(int toPlayer){
	char pos;
	char state;
	if(toPlayer == turn){
		pos = '0' + b->getCurPos();
	}
	else{
		pos = '9';
	}

	if(b->checkFull() == 0) state = VELHA;

	else{
		if(b->checkWin() == 0) state = NADA;
		else if(b->checkWin() == 1){
			if(toPlayer == 1) state = GANHOU;
			else state = PERDEU;
		}
		else if(b->checkWin() == 2){
			if(toPlayer == 1) state = PERDEU;
			else state = GANHOU;
		}
	}

	return "C" + pos + state;
}


