#include "include/server.h"

Server::Server(int nClients, int port) {
	/* Criacao do socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	this->nClients = nClients;

	/* Especifica o endereco para o socket */
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port); // precisa converter o inteiro para o tipo do atributo sin_port
	server_address.sin_addr.s_addr = INADDR_ANY; // endereco pra conectar com qualquer um

	// bind the socket to our specified IP and port
	bind(sock, (struct sockaddr *) &server_address, sizeof(server_address));
}

void Server::waitConnections() {
	listen(sock, nClients);

	for(int i = 0; i < nClients; i++) {
		clients.push_back(accept(sock, NULL, NULL));
		printf("Client %d connected.\n", i);
	}
}

// id do socket
std::string Server::receiveMessage(int id) {
	char msg[256];
	fd_set set;
	struct timeval timeout;
	
	FD_ZERO(&set);
	FD_SET(clients[id-1], &set);
	timeout.tv_sec = TIMEOUT_SECS;
	timeout.tv_usec = TIMEOUT_USECS;
	int rv = select(clients[id-1] + 1, &set, NULL, NULL, &timeout);
	if(rv == 0) {
		//printf("Timeout\n");
		return "";
	}
	else{
		recv(clients[id-1], &msg, sizeof(msg), 0); // recebe a mensagem passada pelo socket
		//printf("The client1 sent data: %s\n", msg);
		return std::string(msg);
	}
}

// envia mensagem para o player (id)
int Server::sendMessage(int id, std::string msg) {
	char men[256];
	
	strcpy(men, msg.c_str());

	return send(clients[id-1], men, sizeof(men), 0); 
}

Server::~Server(){
	close(sock);
}
