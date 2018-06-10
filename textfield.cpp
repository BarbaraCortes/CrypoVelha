#include <memory>
#include <iostream>
#include <GL/glut.h>

#include "include/textfield.h"

TextField::TextField(std::string t, std::function<void(std::string)> h) : text(t), handler(h), Object(0.1, 0.1, 0.4, 0.2) {
	minSize = 4, maxSize = 19;
}

void TextField::onKeyPressed(GLubyte key) {
	switch (key) {
		case 8:
			if (text.size() > minSize) text = text.substr(text.size()-1);
			break;
		case 13:
			handler(text);
			break;
		default:
			if (text.size() < maxSize) text += key;
			break;
	}
}

void TextField::draw(GLfloat x, GLfloat y, GLint screenW, GLint screenH) {
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2f(posX, posY);
		glVertex2f(posX + sizeW, posY);
		glVertex2f(posX + sizeW, posY - sizeH);
		glVertex2f(posX, posY - sizeH);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2f(posX + 5.0 / screenW, posY - 5.0 / screenH);
		glVertex2f(posX + sizeW - 5.0 / screenW, posY - 5.0 / screenH);
		glVertex2f(posX + sizeW - 5.0 / screenW, posY - sizeH + 5.0 / screenH);
		glVertex2f(posX + 5.0 / screenW, posY - sizeH + 5.0 / screenH);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	drawCenterText(text, screenW, screenH);
}
