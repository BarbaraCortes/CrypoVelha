#include "include/object.h"

Object::Object(GLfloat posX, GLfloat posY, GLfloat sizeW, GLfloat sizeH) {
	setCoordinates(posX, posY, sizeW, sizeH);
}

void Object::setCoordinates(GLfloat pX, GLfloat pY, GLfloat sW, GLfloat sH) {
	posX = pX;
	posY = 1.0 - pY;
	sizeW = sW;
	sizeH = sH;
}

void Object::drawCenterText(std::string text, GLint screenW, GLint screenH) {
	glRasterPos2f(posX + sizeW / 2.0 - text.size() * fontW / (2.0 * screenW), posY - sizeH / 2.0);
	for (char c : text) {
		glutBitmapCharacter(font, c);
	}
}
