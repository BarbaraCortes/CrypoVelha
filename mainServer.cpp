#include <bits/stdc++.h>
#include <memory>

#include "include/server.h"
#include "include/client.h"
#include "include/gameController.h"

using namespace std;

enum {
	P1 = 1,
	P2
};

void sendPackages(Server& s, GameController& g) {
	assert(s.sendMessage(P1, g.getBoardPackage()) == 0);
	std::cout << "3" << std::endl;
	assert(s.sendMessage(P1, g.getBigGamePackage()) == 0);
	std::cout << "4" << std::endl;
	assert(s.sendMessage(P1, g.getControlPackage(1)) == 0);
	std::cout << "5" << std::endl;

	assert(s.sendMessage(P2, g.getBoardPackage()) == 0);
	std::cout << "6" << std::endl;
	assert(s.sendMessage(P2, g.getBigGamePackage()) == 0);
	std::cout << "7" << std::endl;
	assert(s.sendMessage(P2, g.getControlPackage(2)) == 0);
	std::cout << "8" << std::endl;
}

int main(){
	int ret;
	Server s(2, 5555);
	GameController g;

	s.waitConnections();
	


	std::cout << "1" << std::endl;

	// Manda o jogo inicial
	sendPackages(s, g);

	std::cout << "2" << std::endl;
	

	string msg;
	while(true){
		std::cout << "taqui\n";
		msg = s.receiveMessage(P1);

		if(msg == "quit"){
			s.sendMessage(P2, "quit");
			break;
		}

		if(msg != "" and g.isTurn(P1)){
			ret = g.userInput(msg, P1);
			if(ret == 1) s.sendMessage(P1, "EPosicao invalida");
			else sendPackages(s, g);
		}

		else if(msg != "" and g.isTurn(P1) == 0){
			s.sendMessage(P1, "ENao eh sua vez");
		}


		msg = s.receiveMessage(P2);
		if(msg == "quit"){
			s.sendMessage(P1, "quit");
			break;
		}

		if(msg != "" and g.isTurn(P2)){
			ret = g.userInput(msg, P2);
			if(ret == 1) s.sendMessage(P2, "EPosicao invalida");
			else sendPackages(s, g);
		}
		else if(msg != "" and g.isTurn(P2) == 0){
			s.sendMessage(P2, "ENao eh sua vez");
		}
	}

	return 0;

}
