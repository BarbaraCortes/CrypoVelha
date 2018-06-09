#include "Fonts.h"
#include <iostream>

sf::Font Fonts::sansation;
sf::Font Fonts::courier;

 void Fonts::load() {
	Fonts::sansation = sf::Font();
	if(Fonts::sansation.loadFromFile("res/sansation.ttf") == 0) std::cout << "Nao carregou sansation" << std::endl;
	Fonts::courier = sf::Font();
	if(Fonts::courier.loadFromFile("res/courier.ttf") == 0) std::cout << "Nao carregou courier" << std::endl;
}