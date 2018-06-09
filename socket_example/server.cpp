#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

/* Necessario para a conexao do socket -> criacao de enderecos (adress e port) do socket que queremos conectar */
#include <netinet/in.h>

int main() {
	char server_message[256] = "You have reached the server!";

	/* Criacao do socket */
	int server_socket;
	server_socket = socket(PF_INET, SOCK_STREAM, 0);

	/* Especifica o endereco para o socket */
	struct sockaddr_in server_address;
	server_address.sin_family = PF_INET;
	server_address.sin_port = htons(8080); // precisa converter o inteiro para o tipo do atributo sin_port
	server_address.sin_addr.s_addr = INADDR_ANY; // endereco pra conectar com qualquer um

	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// Ouve se alguem requisita uma conexao
	listen(server_socket, 4);

	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	// Manda a mensagem
	send(client_socket, server_message, sizeof(server_message), 0);

	// Fecha o socket
	// close(server_socket);

	return 0;
}