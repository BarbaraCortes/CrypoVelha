#include <string.h>
#include <iostream>

using namespace std;

#define mp make_pair
#define fi first
#define se second

class Game {
public:
	int mat[3][3];
	Game() {
		memset(mat, 0, sizeof(mat));
	}
	
	int checkWin() {
		for (int i = 0; i < 3; i++) {
			if (mat[i][0] && mat[i][0] == mat[i][1] && mat[i][0] == mat[i][2]) return mat[i][0];
		}

		for (int j = 0; j < 3; j++) {
			if (mat[0][j] && mat[0][j] == mat[1][j] && mat[0][j] == mat[2][j]) return mat[0][j];
		}

		if (mat[0][0] && mat[0][0] == mat[1][1] && mat[0][0] == mat[2][2]) return mat[0][0];
		if (mat[0][2] && mat[0][2] == mat[1][1] && mat[0][2] == mat[2][0]) return mat[0][2];

		return 0;
	}

	bool checkFull() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (mat[i][j] == 0) return false;
			}
		}
		
		return true;
	}

	bool validPos(int i, int j) {
		return (mat[i][j] == 0);
	}
};

class BigGame {
public:
	Game tab[3][3];
	pair<int, int> curGame;

	BigGame() {
		curGame = mp(-1, -1);
	};
	
	int checkWin() {
		for (int i = 0; i < 3; i++) {
			if (tab[i][0].checkWin() && tab[i][0].checkWin() == tab[i][1].checkWin() && tab[i][0].checkWin() == tab[i][2].checkWin()) 
				return tab[i][0].checkWin();
		}

		for (int j = 0; j < 3; j++) {
			if (tab[0][j].checkWin() && tab[0][j].checkWin() == tab[1][j].checkWin() && tab[0][j].checkWin() == tab[2][j].checkWin()) 
				return tab[0][j].checkWin();
		}

		if (tab[0][0].checkWin() && tab[0][0].checkWin() == tab[1][1].checkWin() && tab[0][0].checkWin() == tab[2][2].checkWin()) 
			return tab[0][0].checkWin();
		
		if (tab[0][2].checkWin() && tab[0][2].checkWin() == tab[1][1].checkWin() && tab[0][2].checkWin() == tab[2][0].checkWin()) 
			return tab[0][2].checkWin();

		return 0;
	}
	
	bool checkFull() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (!tab[i][j].checkWin() && !tab[i][j].checkFull()) return false; 
			}
		}
		
		return true;
	}

	bool validPos(pair<int, int> g, pair<int, int> p) {
		return ((g == curGame || curGame == mp(-1, -1)) && tab[g.fi][g.se].validPos(p.fi, p.se));
	}
	
	pair<int, int> setGame(int i, int j) {
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
		return mp(i, j);
	}

	void markPos(pair<int, int> g, pair<int, int> p, int player) {
		if (!validPos(g, p)) {
			throw std::invalid_argument( "posicao invalida" );
		}
		
		tab[g.fi][g.se].mat[p.fi][p.se] = player;
		
		curGame = setGame(p.fi, p.se);
	}
};

void print(BigGame bg) {
	cout << bg.tab[0][0].mat[0][0] << " " << bg.tab[0][0].mat[0][1] << " " << bg.tab[0][0].mat[0][2] << "  ";
	cout << bg.tab[0][1].mat[0][0] << " " << bg.tab[0][1].mat[0][1] << " " << bg.tab[0][1].mat[0][2] << "  ";
	cout << bg.tab[0][2].mat[0][0] << " " << bg.tab[0][2].mat[0][1] << " " << bg.tab[0][2].mat[0][2] << endl;

	cout << bg.tab[0][0].mat[1][0] << " " << bg.tab[0][0].mat[1][1] << " " << bg.tab[0][0].mat[1][2] << "  ";
	cout << bg.tab[0][1].mat[1][0] << " " << bg.tab[0][1].mat[1][1] << " " << bg.tab[0][1].mat[1][2] << "  ";
	cout << bg.tab[0][2].mat[1][0] << " " << bg.tab[0][2].mat[1][1] << " " << bg.tab[0][2].mat[1][2] << endl;

	cout << bg.tab[0][0].mat[2][0] << " " << bg.tab[0][0].mat[2][1] << " " << bg.tab[0][0].mat[2][2] << "  ";
	cout << bg.tab[0][1].mat[2][0] << " " << bg.tab[0][1].mat[2][1] << " " << bg.tab[0][1].mat[2][2] << "  ";
	cout << bg.tab[0][2].mat[2][0] << " " << bg.tab[0][2].mat[2][1] << " " << bg.tab[0][2].mat[2][2] << endl;

	cout << endl;

	cout << bg.tab[1][0].mat[0][0] << " " << bg.tab[1][0].mat[0][1] << " " << bg.tab[1][0].mat[0][2] << "  ";
	cout << bg.tab[1][1].mat[0][0] << " " << bg.tab[1][1].mat[0][1] << " " << bg.tab[1][1].mat[0][2] << "  ";
	cout << bg.tab[1][2].mat[0][0] << " " << bg.tab[1][2].mat[0][1] << " " << bg.tab[1][2].mat[0][2] << endl;

	cout << bg.tab[1][0].mat[1][0] << " " << bg.tab[1][0].mat[1][1] << " " << bg.tab[1][0].mat[1][2] << "  ";
	cout << bg.tab[1][1].mat[1][0] << " " << bg.tab[1][1].mat[1][1] << " " << bg.tab[1][1].mat[1][2] << "  ";
	cout << bg.tab[1][2].mat[1][0] << " " << bg.tab[1][2].mat[1][1] << " " << bg.tab[1][2].mat[1][2] << endl;

	cout << bg.tab[1][0].mat[2][0] << " " << bg.tab[1][0].mat[2][1] << " " << bg.tab[1][0].mat[2][2] << "  ";
	cout << bg.tab[1][1].mat[2][0] << " " << bg.tab[1][1].mat[2][1] << " " << bg.tab[1][1].mat[2][2] << "  ";
	cout << bg.tab[1][2].mat[2][0] << " " << bg.tab[1][2].mat[2][1] << " " << bg.tab[1][2].mat[2][2] << endl;

	cout << endl;

	cout << bg.tab[2][0].mat[0][0] << " " << bg.tab[2][0].mat[0][1] << " " << bg.tab[2][0].mat[0][2] << "  ";
	cout << bg.tab[2][1].mat[0][0] << " " << bg.tab[2][1].mat[0][1] << " " << bg.tab[2][1].mat[0][2] << "  ";
	cout << bg.tab[2][2].mat[0][0] << " " << bg.tab[2][2].mat[0][1] << " " << bg.tab[2][2].mat[0][2] << endl;

	cout << bg.tab[2][0].mat[1][0] << " " << bg.tab[2][0].mat[1][1] << " " << bg.tab[2][0].mat[1][2] << "  ";
	cout << bg.tab[2][1].mat[1][0] << " " << bg.tab[2][1].mat[1][1] << " " << bg.tab[2][1].mat[1][2] << "  ";
	cout << bg.tab[2][2].mat[1][0] << " " << bg.tab[2][2].mat[1][1] << " " << bg.tab[2][2].mat[1][2] << endl;

	cout << bg.tab[2][0].mat[2][0] << " " << bg.tab[2][0].mat[2][1] << " " << bg.tab[2][0].mat[2][2] << "  ";
	cout << bg.tab[2][1].mat[2][0] << " " << bg.tab[2][1].mat[2][1] << " " << bg.tab[2][1].mat[2][2] << "  ";
	cout << bg.tab[2][2].mat[2][0] << " " << bg.tab[2][2].mat[2][1] << " " << bg.tab[2][2].mat[2][2] << endl;
}

int main() {
	BigGame bg;
	int player = 1;

	print(bg);
	// cout << endl << "jogo atual: " << bg.curGame.fi << ", " << bg.curGame.se << endl;

	while (true) {
		int a, b, c, d;
		cout << endl;
		cin >> a >> b >> c >> d;
		cout << endl;

		bg.markPos(mp(a, b), mp(c, d), player);

		// cout << endl << "jogo atual: " << bg.curGame.fi << ", " << bg.curGame.se << endl;

		if (bg.checkWin()) {
			cout << bg.checkWin() << " ganhou!" << endl;
			break;
		} 

		if (bg.checkFull()) {
			cout << "deu velha" << endl;
			break;
		}

		print(bg);
		player = 3 - player;
	}

	return 0;
}