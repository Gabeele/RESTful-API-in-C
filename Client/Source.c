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

	
	
	WSACleanup();
	return 0;
}