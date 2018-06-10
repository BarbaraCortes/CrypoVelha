#include <iostream>
#include <GL/glut.h>

#include "include/label.h"

Label::Label(std::string t) : text(t), Object(0.1, 0.1, 0.4, 0.2) {

}

void Label::draw(GLfloat x, GLfloat y, GLint screenW, GLint screenH) {
	glColor3f(1.0, 1.0, 1.0);
	drawCenterText(text, screenW, screenH);
}