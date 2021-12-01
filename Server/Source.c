///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project


#include "Server.h"

int main(void) {

	WSADATA data;

	if (WSAStartup(MAKEWORD(2, 2), &data)) {
		fprintf(stderr, "Error: Failed to initlize\n");
		return 1;
	}

	//Server

	struct addrinfo* server_address = ConfigureLocalAddress();

	SOCKET server_socket = CreateListeningSocket(server_address);

	ConnectionListen(server_socket);



	return 1;
}
