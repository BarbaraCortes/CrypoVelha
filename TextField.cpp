#include "TextField.h"
#include <iostream>
using namespace std;

TextField::TextField(int x, int y, int max, int sz) : active(false) {
	this->x = x;
	this->y = y;
	this->max = max;
	this->sz = sz;

	sf::FloatRect r;

	rect = sf::RectangleShape(sf::Vector2f(sz * max, sz + 4));
	r = rect.getLocalBounds();
	rect.setOrigin(r.left + r.width/2, r.top + r.height/2);
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color::White);

	text.setString(sf::String(""));
	text.setFont(Fonts::courier);
	text.setCharacterSize(sz);
	text.setPosition(x - (sz * max)/2, y - sz/2);
	text.setFillColor(sf::Color::Black);
	
}

void TextField::addChar(char c) {
	string s;
	s += c;
	if(text.getString().getSize() < max) {
		text.setString(text.getString() + s);
	}
}

void TextField::removeChar() {
	int sz = text.getString().getSize();
	text.setString(text.getString().substring(0, sz-1));
}

void TextField::draw(sf::RenderWindow & w) {
	if(active) {
		w.draw(rect);
		w.draw(text);
	}
}
