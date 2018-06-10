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

#define TIMEOUT_SECS 0
#define TIMEOUT_USECS 500

class Client {
public:
	int sock;
	int port;
	std::string ip;
	struct sockaddr_in servAddress;
	
	/* Construtor de um cliente */
	Client(std::string ip, int port);

	/* Cria uma conexao e retorna se houve erro */ 
	int createConnection(); 

	/* Recebe um mensagem do servidor e a retorna */
	std::string receiveMessage();

	/* Envia uma mensagem ao servidor e retorna se houve erro */
	int sendMessage(std::string msg);

	/* Destrutor de um cliente */
	~Client();
};

#endif
