#include <memory>
#include <iostream>
#include <cmath>
#include <GL/glut.h>

#include "include/gameboard.h"

GameBoard::GameBoard()
 : finished(false), Object(0.1, 0.1, 0.8, 0.8), cellCallback(nullptr),
   selectedBlockRow(-1), selectedBlockCol(-1) {

}

void GameBoard::onKeyPressed(GLubyte key) {
	switch (key) {
		case 27:
			finished = true;
			break;
	}
}

void GameBoard::onClick(GLfloat mouseX, GLfloat mouseY) {
	mouseX -= posX, mouseY = posY - mouseY;
	GLint bX = floor(mouseX / (sizeW / 3.0)), bY = floor(mouseY / (sizeH / 3.0));
	GLint cX = floor(mouseX / (sizeW / 9.0)) - 3 * bX, cY = floor(mouseY / (sizeH / 9.0)) - 3 * bY;
	if (isSelected(bY, bX) && cellCallback) {
		cellCallback(bY, bX, cY, cX);
	}
}

void GameBoard::drawMark(GLint kind, GLfloat x, GLfloat y, GLfloat sizeW, GLfloat sizeH, GLint screenW, GLint screenH) {
	if (kind) {
		glColor3f(244 / 255.0, 66 / 255.0, 66 / 255.0);
		glLineWidth(2.0);
		glBegin(GL_LINE_STRIP);
			glVertex2f(x + 15.0 / screenW, y - 15.0 / screenH);
			glVertex2f(x + sizeW - 15.0 / screenW, y - sizeH + 15.0 / screenH);
		glEnd();
		glBegin(GL_LINE_STRIP);
			glVertex2f(x + sizeW - 15.0 / screenW, y - 15.0 / screenH);
			glVertex2f(x + 15.0 / screenW, y - sizeH + 15.0 / screenH);
		glEnd();
	} else {
		glColor3f(0 / 255.0, 0 / 255.0, 255 / 255.0);
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		GLfloat cx = x + sizeW / 2.0, cy = y - sizeH / 2.0;
		GLfloat r = std::min(sizeW, sizeH) / 2.0 - 15.0 / std::min(screenH, screenW);
		for (GLint i = 0; i < 360; i++) {
			GLfloat theta = i * (2 * acos(-1.0) / 360);
			glVertex2f(cx + r * sin(theta), cy + r * cos(theta));
		}
		glEnd();
	}
}

void GameBoard::drawBoard(GLfloat posX, GLfloat posY, GLfloat sizeW, GLfloat sizeH, GLfloat screenW, GLfloat screenH) {
	glColor3f(1.0, 1.0, 1.0);
	for (GLint k = 1; k < 3; k++) {
		glBegin(GL_LINE_STRIP);
			glVertex2f(posX + k * (sizeW / 3.0), posY - 5.0 / screenH);
			glVertex2f(posX + k * (sizeW / 3.0), posY - sizeH + 5.0 / screenH);
		glEnd();
	
		glBegin(GL_LINE_STRIP);
			glVertex2f(posX + 5.0 / screenW, posY - k * (sizeH / 3.0));
			glVertex2f(posX + sizeW - 5.0 / screenW, posY - k * (sizeH / 3.0));
		glEnd();
	}
}

void GameBoard::draw(GLfloat x, GLfloat y, GLint screenW, GLint screenH) {
	glLineWidth(5.0);
	drawBoard(posX, posY, sizeW, sizeH, screenW, screenH);

	for (GLint i = 0; i < 3; i++) {
		for (GLint j = 0; j < 3; j++) {
			if (isSelected(i, j)) {
				glColor3f(113 / 255.0, 5 / 255.0, 127 / 255.0);
				glBegin(GL_QUADS);
					glVertex2f(posX + j * (sizeW / 3.0) + 5.0 / screenW, posY - i * (sizeH / 3.0) - 5.0 / screenH);
					glVertex2f(posX + (j + 1) * (sizeW / 3.0) - 5.0 / screenW, posY - i * (sizeH / 3.0) - 5.0 / screenH);
					glVertex2f(posX + (j + 1) * (sizeW / 3.0) - 5.0 / screenW, posY - (i + 1) * (sizeH / 3.0) + 5.0 / screenH);
					glVertex2f(posX + j * (sizeW / 3.0) + 5.0 / screenW, posY - (i + 1) * (sizeH / 3.0) + 5.0 / screenH);
				glEnd();
			}
			glLineWidth(1.0);
			if (board.bigMat[i][j]) {
				drawMark(!(board.bigMat[i][j] - 1), posX + j * (sizeW / 3.0), posY - i * (sizeH / 3.0), sizeW / 3.0, sizeH / 3.0, screenW, screenH);
			} else {
				drawBoard(posX + j * (sizeW / 3.0), posY - i * (sizeH / 3.0), sizeW / 3.0, sizeH / 3.0, screenW, screenH);
			}
		}
	}

	for (GLint i = 0; i < 9; i++) {
		for (GLint j = 0; j < 9; j++) {
			if (board.mat[i][j] && !board.bigMat[i / 3][j / 3]) {
				drawMark(!(board.mat[i][j] - 1), posX + j * (sizeW / 9.0), posY - i * (sizeH / 9.0), sizeW / 9.0, sizeH / 9.0, screenW, screenH);
			}
		}
	}

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(posX, posY);
		glVertex2f(posX + sizeW, posY);
		glVertex2f(posX + sizeW, posY - sizeH);
		glVertex2f(posX, posY - sizeH);
	glEnd();
}
