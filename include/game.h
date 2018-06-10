#ifndef GAME_H
#define GAME_H

#include <cstring> 
#include <string>

class Game {
public:
	int mat[3][3]; 

	/* Construtor de um game */
	Game();
	
	/* Determina se o game foi ganho por algum jogador */
	int checkWin();
	
	/* Determina se não ha mais posicoes para serem marcadas naquele game */
	bool checkFull();
	
	/* Determina se uma posicao eh valida, isto eh, se esta livre */
	bool validPos(int i, int j);
	
	/* Transforma o game em uma string */
	std::string toString();
};

#endif
