#include <bits/stdc++.h>
#include "include/server.h"
#include "include/client.h"
#include "include/gameController.h"
using namespace std;


int main(){
	int ret;
	Server *s = new Server(2, 5555);
	GameController *g = new GameController();

	s->waitConnections();

	string msg;
	while(true){
		msg = s->receiveMessage(0);

		if(msg == "quit"){
			s->sendMessage(1, "quit");
			break;
		}

		if(msg != "" and g->isTurn(1)){
			ret = g->userInput(msg, 1);
			if(ret == 1) s->sendMessage(0, "EPosicao invalida");
			else{
				s->sendMessage(0, g->getBoardPackage());
				s->sendMessage(0, g->getBigGamePackage());
				s->sendMessage(0, g->getControlPackage(1));

				s->sendMessage(1, g->getBoardPackage());
				s->sendMessage(1, g->getBigGamePackage());
				s->sendMessage(1, g->getControlPackage(2));
			}
		}

		else if(g->isTurn(1) == 1){
			s->sendMessage(0, "ENao eh sua vez");
		}


		msg = s->receiveMessage(1);
		if(msg == "quit"){
			s->sendMessage(0, "quit");
			break;
		}

		if(msg != "" and g->isTurn(2)){
			ret = g->userInput(msg, 2);
			if(ret == 1) s->sendMessage(1, "EPosicao invalida");
			else{
				s->sendMessage(0, g->getBoardPackage());
				s->sendMessage(0, g->getBigGamePackage());
				s->sendMessage(0, g->getControlPackage(1));

				s->sendMessage(1, g->getBoardPackage());
				s->sendMessage(1, g->getBigGamePackage());
				s->sendMessage(1, g->getControlPackage(2));
			}
		}
	}

	delete g;
	delete s;

	return 0;

}
