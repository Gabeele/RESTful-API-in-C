///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
///Source File on Server - Inialzing the connection and organizes the program flow

#include "RestServices.h"

// TODO: Clear all _s values

int main(void) {
	
	printf("Initalize Windows socket...\n\n");
	InitlaizeWindowsSockets();

	printf("Creating local address...\n\n");
	struct addrinfo* server_address = ConfigureLocalAddress();

	printf("Creating listening socket...\n\n");
	SOCKET listening_socket = CreateListeningSocket(server_address);

	printf("Connecting the listening socket...\n\n");
	ConnectionListen(listening_socket);

	printf("Creating client socket...\n\n");
	SOCKET client_socket = WaitAndConnect(listening_socket);

	printf("Reading server data...\n\n");
	LISTOFPOSTINGS list = readListFromFile();
	printf("Data loaded...\n\n");

	printf("Waiting for requests...\n\n");
	while (1) {

	char request[STRING_BUFFER];
	memset(request, '\0', 2048);

		int bytes_received = ReceiveMessage(request, client_socket);	
		if (bytes_received < 1) {	//Client closes when the bytes received is less than 1
			printf("Client connection closed.");
			break;
		}
		printf("Request received. Parsing and building response...\n\n");
		parsePayloadAndAction(&list, client_socket, request);

	}

	printf("Closing socket connections...\n\n");
	CloseSocketConnection(client_socket);

	printf("Saving server data to file...\n\n");
	saveListToFile(&list);

	printf("Freeing memory...\n\n");
	freeList(&list);

	printf("Cleaning Windows sockets\n\n");
	WindowsSocketsCleanUp();
	return 0;
}
