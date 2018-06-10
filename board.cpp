#include "include/board.h"

Board::Board() : mat(), bigMat() {}

Board::Board(std::string game, std::string bigGame) : mat(), bigMat() {
	 assert(game.size() == 81);
	 assert(bigGame.size() == 9);
	 int cnt = 0;
	 for(int i = 0; i < 9; ++i) {
		 for(int j = 0; j < 9; ++j) {
			 mat[i][j] = game[cnt++] - '0';
		 }
	 }
	 
	 cnt = 0;
	 for(int i = 0; i < 3; ++i) {
		 for(int j = 0; j < 3; ++j) {
			 mat[i][j] = bigGame[cnt++] - '0';
		 }
	 }
}
