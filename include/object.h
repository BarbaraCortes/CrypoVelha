#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glut.h>
#include <iostream>
#include <functional>

class Object {
protected:
	GLfloat posX, posY;
	GLfloat sizeW, sizeH;

	static constexpr void *font = GLUT_BITMAP_9_BY_15;
	static constexpr GLint fontW = 9;

	void drawCenterText(std::string text, GLint screenW, GLint screenH);

public:
	Object(GLfloat posX, GLfloat posY, GLfloat sizeW, GLfloat sizeH);

	void setCoordinates(GLfloat pX, GLfloat pY, GLfloat sW, GLfloat sH);

	virtual bool isInside(GLfloat x, GLfloat y) {
		return posX <= x && x <= posX + sizeW && posY - sizeH <= y && y <= posY;
	}

	virtual void draw(GLfloat mouseX, GLfloat mouseY, GLint screenW, GLint screenH) = 0;
	virtual void onClick(GLfloat mouseX, GLfloat mouseY) { }
	virtual void onKeyPressed(GLubyte key) { }
};

#endif