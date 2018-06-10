#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <string>
#include <assert.h>

class Tabuleiro {
public:
	int mat[9][9];
	int bigMat[3][3];
	
	/* Construtor generico de um tabuleiro */
	Tabuleiro();

	/* Construtor de um tabuleiro com os parametros dos pacotes recebidos pelo servidor */
	Tabuleiro(std::string, std::string);
};

#endif
