#include <bits/stdc++.h>
#include "include/client.h"

using namespace std;

int main(int argc, char * argv[]) {
	Client *c = new Client("192.168.182.162", 5555);
	
	if(c->createConnection() == -1) {
		return 0;
	}
	
	string msg;
	
	while(1)  {
		cin >> msg;
		c->sendMessage(msg);
		if(msg == "quit") break;
		msg = c->receiveMessage();
		if(msg == "quit") break;
		cout << msg << endl;
	}
	
	delete c;
}
