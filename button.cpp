#include <memory>
#include <iostream>
#include <GLUT/glut.h>

#include "include/button.h"

Button::Button(std::string t, std::function<void()> h) : text(t), handler(h), Object(0.1, 0.1, 0.4, 0.2) {

}

void Button::onClick(GLfloat mouseX, GLfloat mouseY) {
	handler();
}

void Button::draw(GLfloat x, GLfloat y, GLint screenW, GLint screenH) {
	if (isInside(x, y)) glColor3f(0.0, 1.0, 0.0);
	else glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_QUADS);
		glVertex2f(posX, posY);
		glVertex2f(posX + sizeW, posY);
		glVertex2f(posX + sizeW, posY - sizeH);
		glVertex2f(posX, posY - sizeH);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	drawCenterText(text, screenW, screenH);
}