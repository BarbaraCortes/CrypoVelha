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
	assert(s.sendMessage(P1, g.getBoardPackage()));
	assert(s.sendMessage(P1, g.getBigGamePackage()));
	assert(s.sendMessage(P1, g.getControlPackage(1)));

	assert(s.sendMessage(P2, g.getBoardPackage()));
	assert(s.sendMessage(P2, g.getBigGamePackage()));
	assert(s.sendMessage(P2, g.getControlPackage(2)));
}

int main(){
	int ret;
	Server s(2, 5555);
	GameController g;

	s.waitConnections();

	sendPackages(s, g);	

	string msg;
	while(true){
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

	s.close();

	return 0;

}
