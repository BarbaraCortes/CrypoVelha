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
		std::cerr << "Erro na conexao." << std::endl;
		sock = -1;
		exit(0);
	}
}

// -1: erro, 0: bacana
int Client::createConnection() {
	int ret = connect(sock, (struct sockaddr *) &servAddress, sizeof(servAddress));
	if (ret == -1) {
		sock = -1;
	}
	return ret;
}

std::string Client::receiveMessage() {
	char msg[256];
	fd_set set;
	struct timeval timeout;
	
	FD_ZERO(&set);
	FD_SET(sock, &set);
	timeout.tv_sec = TIMEOUT_SECS;
	timeout.tv_usec = TIMEOUT_USECS;
	
	int rv = select(sock + 1, &set, NULL, NULL, &timeout);
	if(rv == 0) return "";
	else {
		recv(sock, &msg, sizeof(msg), 0); // recebe a mensagem passada pelo socket
		return std::string(msg);
	}
}


int Client::sendMessage(std::string msg) {
	char men[256];
	strcpy(men, msg.c_str());
	return send(sock, men, sizeof(men), 0); 
}

Client::~Client(){
	if (sock != -1) {
		close(sock);
	}
}
