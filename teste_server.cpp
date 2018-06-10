#include <bits/stdc++.h>
#include "include/server.h"
#include "include/client.h"

using namespace std;


int main(){
	Server *s = new Server(2, 5555);

	s->waitConnections();

	string msg;
	while(true){
		msg = s->receiveMessage(0);
		if(msg != ""){
			cout << "Client 0 sent: " + msg << endl;
			//s->sendMessage(1, msg);
		} 

		if(msg == "quit") break;

		msg = s->receiveMessage(1);
		if(msg != ""){
			cout << "Client 1 sent: " + msg << endl;
			//s->sendMessage(0, msg);
		} 

		if(msg == "quit") break;
	}

	delete s;

	return 0;

}
