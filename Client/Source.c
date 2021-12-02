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
		fprintf(stderr, "Error: Failed to initialize\n");
		return 1;
	}

	//Client

	struct addrinfo* target_address = ConfigureTargetAddress("127.0.0.1", "8080", TCP);

	SOCKET target_socket = CreateConnectionToTargetSocket(target_address);

	char buf[STRING_BUFFER] = "";


	ReceiveMessageFromSocket(buf, target_socket);


	CloseSocketConnection(target_socket);
	WindowsSocketsCleanUp();
	return 0;
}