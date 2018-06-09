#include "include/Button.h"
using namespace std;

Button::Button(int w, int h, int x, int y, string str, sf::Color color = sf::Color::White) {
	this->w = w;
	this->h = h;
	this->x = x;
	this->y = y;
	col = color;
	hoverCol = sf::Color::Green;

	sf::FloatRect r;

	rect = sf::RectangleShape(sf::Vector2f(w, h));
	r = rect.getLocalBounds();
	rect.setOrigin(r.left + r.width/2, r.top + r.height/2);
	rect.setPosition(x, y);
	rect.setFillColor(col);

	text.setString(sf::String(str));
	text.setFont(Fonts::sansation);
	text.setCharacterSize(20);
	r = text.getLocalBounds();
	text.setOrigin(r.left + r.width/2, r.top + r.height/2);

	text.setPosition(x, y);
	text.setFillColor(sf::Color::White);
	
}

void Button::draw(sf::RenderWindow & w) {
	w.draw(rect);
	w.draw(text);
}

bool Button::selecting(int x, int y) {
	sf::FloatRect r;

	r = rect.getGlobalBounds();
	return (x >= r.left and x <= r.left + r.width and y >= r.top and y <= r.top + r.height);
}

void Button::hover(sf::RenderWindow & w) {
	int x = sf::Mouse::getPosition(w).x;
	int y = sf::Mouse::getPosition(w).y;
	if(selecting(x, y)) {
		rect.setFillColor(hoverCol);
	} else {
		rect.setFillColor(col);
	}
}