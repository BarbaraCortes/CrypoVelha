#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Board Board;

struct Board {
	int mat[9][9]; // tabuleiro
	int val[9][9]; // posicoes validas para jogada atual
	int cur_player; // jogador atual
};

void set_val(Board *b, int x, int y) {
	memset(b->val, 0, 9 * sizeof(int));

	for (int i = 3 * (x % 3); i < 3 * (x % 3) + 3; i++) {
		for (int j = 3 * (y % 3); j < 3 * (y % 3) + 3; j++) {
			b->val[i][j] = 1;
		}
	}
}

int is_valid(Board *b, int x, int y) {
	return (b->val[x][y] && !b->mat[x][y]);
}

Board *create_board() {
	return calloc(1, sizeof(Board));
}

int main(int argc, char *argv[]) {
	Board *b;

	b = create_board();

	set_val(b, 0, 8);

	for (int i = 0; i < 9; i++) {
		if (i && i % 3 == 0) printf("\n");
		for (int j = 0; j < 9; j++) {
			if (j && j % 3 == 0) printf(" ");
			printf("%d", b->val[i][j]);
		}
		printf("\n");
	}


	return 0;
}