#include <cassert>
#include <iostream>

#include "include/protocol.h"

Protocol::Protocol() {
	
}

void Protocol::parsePacket(std::string msg) {
	assert(msg.size());
	switch (msg[0]) {
		case 'T': return parseBoard(msg.substr(1));
		case 'B': return parseBigGame(msg.substr(1));
		case 'C': return parseControl(msg.substr(1));
		case 'E': return parseError(msg.substr(1));
		default:
			std::cerr << "Pacote de tipo desconhecido: " << msg[0] << std::endl;
			return;
	}
}

void Protocol::parseBoard(std::string msg) {

}

void Protocol::parseBigGame(std::string msg) {

}

void Protocol::parseControl(std::string msg) {

}

void Protocol::parseError(std::string msg) {

}

