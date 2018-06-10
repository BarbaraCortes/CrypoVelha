#ifndef LABEL_H
#define LABEL_H

#include "object.h"

class Label : public Object {
private:
	std::string text;

public:	

	Label(std::string text);

	void draw(GLfloat x, GLfloat y, GLint screenW, GLint screenH);

	void setText(std::string t) {
		text = t;
	}

	const std::string& getText() {
		return text;
	}
};

#endif