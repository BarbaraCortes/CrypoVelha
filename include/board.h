#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <assert.h>

class Board {
public:
	int mat[9][9];
	int bigMat[3][3];
	
	/* Construtor generico de um Board */
	Board();

	/* Construtor de um Board com os parametros dos pacotes recebidos pelo servidor */
	Board(std::string, std::string);
};

#endif
