///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project

#include "UI.h"


void main() {

	InitlaizeWindowsSockets();

	//Client

	struct addrinfo* target_address = ConfigureTargetAddress("127.0.0.1", "8080");

	SOCKET target_socket = CreateConnectionToTargetSocket(target_address);

	menu();

	char buf[STRING_BUFFER] = "";
	//memset(buf, '\0', STRING_BUFFER);


	//send a post message

	//SendMessageToSocket("POST://", target_socket);

	//ReceiveMessageFromSocket(buf, target_socket);



	CloseSocketConnection(target_socket);
	WindowsSocketsCleanUp();
	return 0;
}