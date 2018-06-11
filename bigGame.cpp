#include "include/bigGame.h"
#include <time.h>
#include <cstdio>
#include <cstdlib>

BigGame::BigGame() {
	// o primeiro jogador devera jogar em um game definido aleatoriamente
	srand(time(NULL));
	curGame = std::make_pair(rand()%3, rand()%3);
}

int BigGame::checkWin() {
	//determina se ganhou em alguma linha
	for (int i = 0; i < 3; i++) {
		if (tab[i][0].checkWin() && tab[i][0].checkWin() == tab[i][1].checkWin() && tab[i][0].checkWin() == tab[i][2].checkWin()) 
			return tab[i][0].checkWin();
	}

	//determina se ganhou em alguma coluna
	for (int j = 0; j < 3; j++) {
		if (tab[0][j].checkWin() && tab[0][j].checkWin() == tab[1][j].checkWin() && tab[0][j].checkWin() == tab[2][j].checkWin()) 
			return tab[0][j].checkWin();
	}

	//determina se ganhou na diagonal principal
	if (tab[0][0].checkWin() && tab[0][0].checkWin() == tab[1][1].checkWin() && tab[0][0].checkWin() == tab[2][2].checkWin()) 
		return tab[0][0].checkWin();
	
	//determina se ganhou na diagonal secundaria
	if (tab[0][2].checkWin() && tab[0][2].checkWin() == tab[1][1].checkWin() && tab[0][2].checkWin() == tab[2][0].checkWin()) 
		return tab[0][2].checkWin();

	// nenhum jogador ganhou ainda
	return 0; 
}

bool BigGame::checkFull() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// ainda se pode jogar nesse game por ha posicoes vazias e ninguem o ganhou
			if (!tab[i][j].checkWin() && !tab[i][j].checkFull()) return false; 
		}
	}
	
	// nao ha mais games para serem jogados
	return true;
}

bool BigGame::validPos(std::pair<int, int> g, std::pair<int, int> p) {
	// uma posicao eh valida caso esteja vazia e pertenca ao game correto
	return (g == curGame && tab[g.first][g.second].validPos(p.first, p.second));
}

std::pair<int, int> BigGame::setGame(int i, int j) {
	// caso o game atual esteja indisponivel passamos ao da direita 
	while (tab[i][j].checkWin() || tab[i][j].checkFull()) {
		j++;
		if (j == 3) {
			i++;
			j = 0;
		}
		if (i == 3) {
			i = 0;
			j = 0;
		}
	}
	return std::make_pair(i, j);
}

bool BigGame::markPos(std::pair<int, int> g, std::pair<int, int> p, int player) {
	// retorna que deu erro caso a posicao que o jogador quer marcar seja invalida
	if (!validPos(g, p)) return false;
	
	// marca a posicao jogada
	tab[g.first][g.second].mat[p.first][p.second] = player;
	
	// determina qual o proximo game a ser jogado
	if (!checkFull()) curGame = setGame(p.first, p.second);
	return true;
}

bool BigGame::checkTie() {
	// se ninguem tiver ganhado mas nao ha mais onde jogar deu velha
	return (checkFull() && !checkWin());
}

std::string BigGame::completeGame() {
	std::string res;
	
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			res += tab[i][j].toString();
		}
	}
	
	return res;
}

std::string BigGame::toString() {
	std::string res;
	
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			res += '0' + tab[i][j].checkWin();
		}
	}
	
	return res;
}

int BigGame::getCurPos() {
	return curGame.first * 3 + curGame.second;
}
