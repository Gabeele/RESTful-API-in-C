///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project


#include "RestServices.h"


int main(void) {
	
	

	InitlaizeWindowsSockets();

	struct addrinfo* server_address = ConfigureLocalAddress();

	SOCKET listening_socket = CreateListeningSocket(server_address);

	ConnectionListen(listening_socket);

	SOCKET client_socket = WaitAndConnect(listening_socket);

	//char message[STRING_BUFFER];

	CloseSocketConnection(listening_socket);

	LISTOFPOSTINGS list = readListFromFile();


	while (1) {

	char request[2048];
	memset(request, '\0', 2048);

		int bytes_received = ReceiveMessage(request, client_socket);
		if (bytes_received < 1) {
			printf("Client connection closed.");
			break;
		}

		parsePayloadAndAction(&list, client_socket, request);

	}

	CloseSocketConnection(client_socket);

	saveListToFile(&list);

	WindowsSocketsCleanUp();
	return 0;
}
