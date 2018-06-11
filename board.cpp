#include "include/board.h"

Board::Board() : mat(), bigMat() {}

Board::Board(std::string game, std::string bigGame) : mat(), bigMat() {
	 assert(game.size() == 81);
	 assert(bigGame.size() == 9);
	 int cnt = 0;
	 for(int i = 0; i < 3; ++i) {
		 for(int j = 0; j < 3; ++j) {
			 for (int k = 0; k < 9; k++) {
				int c = game[cnt++] - '0';
				mat[i * 3 + (k / 3)][j * 3 + (k % 3)] = c;
			 }
		 }
	 }
	 
	 cnt = 0;
	 for(int i = 0; i < 3; ++i) {
		 for(int j = 0; j < 3; ++j) {
			 bigMat[i][j] = bigGame[cnt++] - '0';
		 }
	 }
}
