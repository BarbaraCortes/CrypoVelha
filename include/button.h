#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "object.h"

class Button : public Object {
private:
	std::string text;
	std::function<void()> handler;

public:	

	Button(std::string text, std::function<void()> handler);

	void draw(GLfloat x, GLfloat y, GLint screenW, GLint screenH);
	void onClick(GLfloat mouseX, GLfloat mouseY);
};

#endif