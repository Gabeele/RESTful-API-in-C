///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project


#include "Client.h"

void main() {

	WSADATA data;

	if (WSAStartup(MAKEWORD(2, 2), &data)) {
		fprintf(stderr, "Error: Failed to initlize\n");
		return 1;
	}

	//Client

	struct addrinfo* target_address = ConfigureTargetAddress("127.0.0.1", "8080", TCP);

	SOCKET target_socket = CreateConnectionToTargetSocket(target_address);


	//Send a message 
	char* message = "Hello world :)";

	if (send(target_socket, message, strlen(message), 0) == 0) {
		printf("Sent failed");
		exit(1);
	}

	char reply[STRING_BUFFER];
	memset(reply, '\0', STRING_BUFFER);

	while (recv(target_socket, reply, STRING_BUFFER, 0)== 0);
	
	int bytes_received = recv(accept, reply, STRING_BUFFER, 0);

	printf("%.*s", bytes_received, reply);




	
	WSACleanup();
	return 0;
}