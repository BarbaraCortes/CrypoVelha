#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h> /* Necessario para a conexao do socket -> criacao de enderecos (adress e port) do socket que queremos conectar */
#include <arpa/inet.h>
#include <unistd.h>

class Client {
public:
	int sock;
	std::string ip;
	int port;
	struct sockaddr_in servAddress;
	
	Client(std::string ip, int port);
	int createConnection(); //retorna se houve erro
	std::string receiveMessage();
	int sendMessage(std::string msg);
	~Client();
};

#endif
