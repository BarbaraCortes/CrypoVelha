#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <string>

class Tabuleiro {
public:
	int mat[9][9];
	int bigMat[3][3];
	
	Tabuleiro();
	Tabuleiro(std::string s);
	
};

#endif
