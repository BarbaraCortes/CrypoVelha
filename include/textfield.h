#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <functional>

#include "object.h"

class TextField : public Object {
private:
	std::string text;
	std::function<void(std::string)> handler;

	size_t minSize, maxSize;

public:	

	TextField(std::string text, std::function<void(std::string)> handler);

	void draw(GLfloat x, GLfloat y, GLint screenW, GLint screenH);
	void onKeyPressed(GLubyte key);
};

#endif
