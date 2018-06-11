#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <functional>

#include "object.h"
#include "label.h"
#include "board.h"

class GameBoard : public Object {
private:
	bool finished;

	std::function<void(GLint blockRow, GLint blockCol, GLint line, GLint row)> cellCallback;

	void drawMark(GLint kind, GLfloat x, GLfloat y, GLfloat sizeW, GLfloat sizeH, GLint screenW, GLint screenH);
	void drawBoard(GLfloat posX, GLfloat posY, GLfloat sizeW, GLfloat sizeH, GLfloat screenW, GLfloat screenH);

	GLint selectedBlockRow, selectedBlockCol;

	Board board;

public:	

	GameBoard();

	void draw(GLfloat x, GLfloat y, GLint screenW, GLint screenH);
	void onKeyPressed(GLubyte key);
	void onClick(GLfloat mouseX, GLfloat mouseY);

	bool isFinished() {
		return finished;
	}

	void setCellCallback(std::function<void(GLint blockRow, GLint blockCol, GLint line, GLint row)> callback) {
		cellCallback = callback;
	}

	bool isSelected(GLint blockRow, GLint blockCol) {
		return selectedBlockRow == blockRow && selectedBlockCol == blockCol;
	}

	void setSelectedBlock(GLint row, GLint col) {
		selectedBlockRow = row;
		selectedBlockCol = col;
	}

	void setBoard(Board b) {
		board = b;
	}
};

#endif
