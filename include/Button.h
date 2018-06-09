#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Fonts.h"

using namespace std;

class Button {
public:
	sf::Text text;
	sf::Color col, hoverCol;
	sf::RectangleShape rect;
	int w, h, x, y;

	Button(){}
	Button(int w, int h, int x, int y, string str, sf::Color color);
	void draw(sf::RenderWindow & w);
	bool selecting(int x, int y);
	void hover(sf::RenderWindow & w);
};

#endif