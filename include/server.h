#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h> /* Necessario para a conexao do socket -> criacao de enderecos (adress e port) do socket que queremos conectar */

#define TIMEOUT_SECS 1
#define TIMEOUT_USECS 0

class Server {
public:
	int nClients;
	int sock;
	std::vector<int> clients;
	
	Server(int nClients, int port);
	void waitConnections();
	std::string receiveMessage(int id); // id do socket
	int sendMessage(int id, std::string msg); // envia mensagem para o player (id)
};

#endif
