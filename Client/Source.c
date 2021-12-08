///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project

#include "UI.h"

#define ZERO_BYTE_MESSAGE ""


void main() {

	InitlaizeWindowsSockets();

	struct addrinfo* target_address = ConfigureTargetAddress("127.0.0.1", "8080");

	SOCKET target_socket = CreateConnectionToTargetSocket(target_address);

	

	//send a post message

	while (1) {
		char response[STRING_BUFFER];
		memset(response, '\0', STRING_BUFFER);

		if (menu(target_socket) == 1) {
			SendMessageToSocket(ZERO_BYTE_MESSAGE, target_socket);
			break;
		}
	
		int bytes_recieved = ReceiveMessageFromSocket(response, target_socket);

		if (bytes_recieved == 0) {
			printf("Server connection closed.");
			break;
		}


	}

	shutdown(target_socket, SD_SEND);
	CloseSocketConnection(target_socket);
	WindowsSocketsCleanUp();
	return 0;
}