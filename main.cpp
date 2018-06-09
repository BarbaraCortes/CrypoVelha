#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Fonts.h"
#include "Button.h"
#include "TextField.h"
#include <string>
#include <iostream>
#include <cstdlib>

#define WINDOW_WIDTH 360
#define WINDOW_HEIGHT 360

using namespace std;

sf::RenderWindow window;
Button new_game;
Button connect;
TextField field;
sf::Text erro;

bool validIP(string s) {
	int cnt = 0;
	s += '.';
	char last = '.';
	for(int i = 0; i < s.size(); ++i) {
		if(s[i] == '.') {
			cnt++;
			if(last == '.') return false;
		}
		last = s[i];
	}
	return cnt == 4;
}

void handleInput() {
	sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed) {
            window.close();
        }
        else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
        	if(new_game.selecting(event.mouseButton.x, event.mouseButton.y)) {
        		cout << "Novo jogo" << endl;
        		system("./server");
        		exit(0);
        	} else if(connect.selecting(event.mouseButton.x, event.mouseButton.y)) {
        		cout << "Conect" << endl;
        		field.active = !field.active;
        	}
        }
        else if(event.type == sf::Event::TextEntered) {
        	if(field.active) {

        		if(event.text.unicode == '\b') {
        			field.removeChar();

        		}
        		else if(event.text.unicode == '\n') {
        			string s = field.text.getString();
        			if(validIP(s)) {
        				string t = "./client " + s; 
	        			// Vai acabar o programa
	        			system(t.c_str());
	        			exit(0);
        			} else erro.setString("IP invalido");
        		}
        		else if(event.text.unicode < 128) { //eh um char
        			char c = static_cast<char>(event.text.unicode);
        			if(isdigit(c) or c == '.') {
        				field.addChar(c);
        				erro.setString("");
        			}
        			else erro.setString("Caractere invalido");
        		}
        	}
        }
    }
}

void draw() {
	window.clear(sf::Color::Black);
	new_game.draw(window);
	connect.draw(window);
	field.draw(window);
	window.draw(erro);
	
	window.display();
}

void gameLoop() {
	while (window.isOpen())
    {
       
    	handleInput();

		new_game.hover(window);
		connect.hover(window);
		draw();
    }
}

int main() {

	Fonts::load();

	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CryptoVelha");

	new_game = Button(200, 50, WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - 35, "Novo jogo", sf::Color::Blue);
	connect = Button(200, 50, WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + 35, "Conectar a existente", sf::Color::Blue);
	field = TextField(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + 90, 15, 15);

	// Mensagem de erro no final
	erro.setFont(Fonts::courier);
	erro.setPosition(4, WINDOW_HEIGHT - 20);
	erro.setFillColor(sf::Color::White);
	erro.setCharacterSize(15);
	erro.setString("");

	gameLoop();

}