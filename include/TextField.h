#ifndef FIELD_H
#define FIELD_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Fonts.h"

using namespace std;

class TextField {
public:
	sf::Text text;
	sf::RectangleShape rect;
	int x, y;
	int sz; //character size
	int max; //maximo num de caracteres
	bool active;

	TextField(){}
	TextField(int x, int y, int max, int sz);
	void draw(sf::RenderWindow & w);
	void addChar(char c);
	void removeChar();
};

#endif