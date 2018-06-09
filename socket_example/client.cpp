#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

/* Necessario para a conexao do socket -> criacao de enderecos (adress e port) do socket que queremos conectar */
#include <netinet/in.h>

using namespace std;

string getIPAddress(){
    string ipAddress="Unable to get IP Address";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if(strcmp(temp_addr->ifa_name, "en0") == 0){
                    ipAddress=inet_ntoa(((struct sockaddr_in*)temp_addr->ifa_addr)->sin_addr);
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    // Free memory
    freeifaddrs(interfaces);
    return ipAddress;
}

int main() {

	cout << getIPAddress() << endl;

	/* Criacao do socket */
	int network_socket;
	network_socket = socket(PF_INET, SOCK_STREAM, 0);

	/* Especifica o endereco para o socket*/
	struct sockaddr_in server_address;
	server_address.sin_family = PF_INET;
	server_address.sin_port = htons(8080); // precisa converter o inteiro para o tipo do atributo sin_port
	// server_address.sin_addr.s_addr = INADDR_ANY; // endereco pra conectar com qualquer um
	if(inet_pton(PF_INET, "172.26.157.129", &server_address.sin_addr) <= 0) {
		printf("ERro\n");
		return 0;
	}
	int connection = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address)); // retorna se houve erro

	// check for error with the connection
	if (connection == -1) {
		printf("There was an error making a connection to the remote socket.\n\n");
	}

	// receive data from the server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0); // recebe a mensagem passada pelo socket

	// print out the server's response
	printf("The server sent the data: %s\n", server_response);

	// close(network_socket);
	return 0;
}