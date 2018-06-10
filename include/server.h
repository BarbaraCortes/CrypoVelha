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
#include <unistd.h>

#define TIMEOUT_SECS 0
#define TIMEOUT_USECS 500

class Server {
public:
	int nClients;
	int sock;
	std::vector<int> clients;
	
	/* Construtor de um servidor */
	Server(int nClients, int port);

	/* Espera pela conexao de clientes */
	void waitConnections();

	/* Recebe uma mensagem do cliente e a retorna */
	std::string receiveMessage(int id); // id do socket

	/* Envia uma mensagem para o player [id] e retorna se houve erro */
	int sendMessage(int id, std::string msg); 

	/* Destrutor de um servidor */
	~Server();
};

#endif
