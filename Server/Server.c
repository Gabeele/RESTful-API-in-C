///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project

#include "Server.h"

struct addrinfo* ConfigureLocalAddress() {
	char ip_address[IP_ADDRESS_MAX] = "";
	char port[PORT_NUMBER_MAX] = "8080";
	struct addrinfo info;
	
	memset(&info, 0, sizeof(info));

	info.ai_family = AF_INET;
	info.ai_socktype = SOCK_STREAM;
	info.ai_flags = AI_PASSIVE;

	struct addrinfo* address;
	getaddrinfo(0, "8080", &info, &address);

	return address;
}

SOCKET CreateListeningSocket(struct addrinfo* address) {
	SOCKET sock; 

	sock = socket(address->ai_family, address->ai_socktype, address->ai_protocol);

	if (sock == INVALID_SOCKET) {
		fprintf(stderr, "Error: Failed to configure local socket\n");
		exit(1);
	}

	if (bind(sock, address->ai_addr, address->ai_addrlen)) {
		fprintf(stderr, "Error: Failed to bind local socket\n");
		exit(1);
	}

	//free(address);

	return sock;

}

void ConnectionListen(SOCKET socket) {

	if (listen(socket, MAXLISTENERS) < 0) {
		fprintf(stderr, "Error: Listen failed\n");
		exit(1);
	}

}

SOCKET WaitAndConnect(SOCKET socket) {
	struct sockaddr_storage client_address;
	struct sockaddr* socket_address_client = (struct sockaddr*)&client_address;
	socklen_t length_of_client;
	SOCKET client_socket;
	char address_buffer[STRING_BUFFER];

	length_of_client = sizeof(client_address);

	client_socket = accept(socket, socket_address_client, &length_of_client);	//Accepts the first of the threeway handshake

	if (client_socket == INVALID_SOCKET) {
		fprintf(stderr, "Error: Accepted failed\n");
		exit(1);
	}

	getnameinfo(socket_address_client, length_of_client, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);

	printf("Client address is: %s", address_buffer);

	return client_socket;
}