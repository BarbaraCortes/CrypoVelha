#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

class Protocol {
protected:

public:
	Protocol();

	void parsePacket(std::string msg);

	void parseBoard(std::string msg);
	void parseBigGame(std::string msg);
	void parseControl(std::string msg);
	void parseError(std::string msg);
};

#endif