#ifndef BIGGAME_H
#define BIGGAME_H

#include <utility>
#include "include/game.h"
#include <cstring>
#include <string>

class BigGame {

private:
	/* Estabelece qual será o game onde o proximo jogador devera jogar */
	std::pair<int, int> setGame(int i, int j);
	
	/* Determina se uma posicao eh valida, isto eh, esta desocupada e pertence ao game correto */
	bool validPos(std::pair<int, int> g, std::pair<int, int> p);
	
public:
	Game tab[3][3];
	std::pair<int, int> curGame;

	/* Construtor de um BigGame */
	BigGame();

	/* Checa se um jogador ganhou o BigGame */
	int checkWin();

	/* Checa se não ha mais posicoes para serem marcadas no BigGame */
	bool checkFull();

	/* Checa se o jogo deu velha */
	bool checkTie();

	/* Marca no tabuleiro a posicao onde o jogador decidiu jogar */
	bool markPos(std::pair<int, int> g, std::pair<int, int> p, int player);

	/* Retorna a string de 81 caracteres */
	std::string completeGame();

	/* Transforma o BigGame em uma string */
	std::string toString();
	int getCurPos();
};


#endif
