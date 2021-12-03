///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project



#include "PostingList.h"
#include "Server.h"

int main(void) {

	p_ListOfPostings list = readListFromFile();

	InitlaizeWindowsSockets();

	struct addrinfo* server_address = ConfigureLocalAddress();

	SOCKET server_socket = CreateListeningSocket(server_address);

	ConnectionListen(server_socket);

	//SOCKET client_socket = WaitAndConnect(server_socket);	

	char message[STRING_BUFFER];

	//ReceiveMessageAndRespondFromSocket(message, client_socket);

	addToList(list, "Gavin", "Plants");
	addToList(list, "Baxter", "Korea");

	saveListToFile(list);
	//CloseSocketConnection(client_socket);
	WindowsSocketsCleanUp();
	return 0;
}
