#include "include/client.h"

Client::Client(std::string ip, int port) {
	
	this->ip = ip;
	this->port = port;
	/* Criacao do socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);

	/* Especifica o endereco para o socket*/
	servAddress.sin_family = AF_INET;
	servAddress.sin_port = htons(port); // precisa converter o inteiro para o tipo do atributo sin_port
	if(inet_pton(AF_INET, ip.c_str(), &servAddress.sin_addr) <= 0) {
		printf("Erro\n");
	}
}

// -1: erro, 0: bacana
int Client::createConnection() {
	int ret = connect(sock, (struct sockaddr *) &servAddress, sizeof(servAddress));
	if(ret == -1) printf("Erro ao conectar ao socket");
	return ret;
}

std::string Client::receiveMessage() {
	char msg[256];
	recv(sock, &msg, sizeof(msg), 0); // recebe a mensagem passada pelo socket
	return std::string(msg);
}


int Client::sendMessage(std::string msg) {
	char men[256];
	strcpy(men, msg.c_str());
	return send(sock, men, sizeof(men), 0); 
}

Client::~Client(){
	close(sock);
}
