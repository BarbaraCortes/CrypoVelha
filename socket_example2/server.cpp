#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

/* Necessario para a conexao do socket -> criacao de enderecos (adress e port) do socket que queremos conectar */
#include <netinet/in.h>

int main() {
	char server_message[256] = "You have reached the server!";

	/* Criacao do socket */
	int server_socket;
	server_socket = socket(PF_INET, SOCK_STREAM, 0);

	/* Especifica o endereco para o socket */
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080); // precisa converter o inteiro para o tipo do atributo sin_port
	server_address.sin_addr.s_addr = INADDR_ANY; // endereco pra conectar com qualquer um

	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// Ouve se alguem requisita uma conexao
	listen(server_socket, 4);

	int client_socket1;
	int client_socket2;
	client_socket1 = accept(server_socket, NULL, NULL);
	printf("Client1 connected.\n");
	client_socket2 = accept(server_socket, NULL, NULL);
	printf("Client2 connected.\n");

	fd_set set1;
	fd_set set2;
	struct timeval timeout;

	char client_response1[256];
	char client_response2[256];
	while(true){
		FD_ZERO(&set1);
		FD_ZERO(&set2);
		FD_SET(client_socket1, &set1);
		FD_SET(client_socket2, &set2);
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		int rv = select(client_socket1 + 1, &set1, NULL, NULL, &timeout);
		if(rv == 0){
			printf("Timeout.\n");
		}
		else{
			recv(client_socket1, &client_response1, sizeof(client_response1), 0); // recebe a mensagem passada pelo socket
			printf("The client1 sent data: %s\n", client_response1);
			send(client_socket2, client_response1, sizeof(client_response1), 0);

		}

		rv = select(client_socket2 + 1, &set2, NULL, NULL, &timeout);
		if(rv == 0){
			printf("Timeout.\n");
		}
		else{
			recv(client_socket2, &client_response2, sizeof(client_response2), 0); // recebe a mensagem passada pelo socket
			printf("The client2 sent data: %s\n", client_response2);
			send(client_socket1, client_response2, sizeof(client_response2), 0);
		}

	}

	// Fecha o socket
	// close(server_socket);

	return 0;
}
