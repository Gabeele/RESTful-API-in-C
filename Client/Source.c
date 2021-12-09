///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
///Source File on Client - Inizalizes, creates, and manages the socket sending and receiving. 

#include "UI.h"

#define ZERO_BYTE_MESSAGE ""

void main() {

	printf("Initalize Socket\n");
	InitlaizeWindowsSockets();

	printf("Creating target address...\n");
	struct addrinfo* target_address = ConfigureTargetAddress(IP_ADDRESS, PORT_NUMBER);

	printf("Creating target socket...\n");
	SOCKET target_socket = CreateConnectionToTargetSocket(target_address);

	while (1) {
		char response[STRING_BUFFER];
		memset(response, '\0', STRING_BUFFER);

		if (menu(target_socket) == 1) {
			SendMessageToSocket(ZERO_BYTE_MESSAGE, target_socket);	//Sends a zero byte message to close
			break;

		}

		if (ReceiveMessageFromSocket(response, target_socket) == 0) {	
			printf("Server connection closed.");
			break;

		}

		pressToContinute();

	}

	printf("Closing target socket...\n");
	CloseSocketConnection(target_socket);

	printf("Socket cleanup ...\n");
	WindowsSocketsCleanUp();

	return 0;
}