///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
/// Server C File on Server - Manages connection functions 

#include "Server.h"
/// <summary>
/// Inializies Windows sockets
/// </summary>
void InitlaizeWindowsSockets() {

	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data))
	{
		fprintf(stderr, "Error: Failed to initialize\n");
		exit(1);
	}

}

/// <summary>
/// Creates a addrinfo defined as it's local address
/// </summary>
struct addrinfo* ConfigureLocalAddress() {
	struct addrinfo info;
	
	memset(&info, 0, sizeof(info));

	info.ai_family = AF_INET;
	info.ai_socktype = SOCK_STREAM;
	info.ai_flags = AI_PASSIVE;

	struct addrinfo* address;
	getaddrinfo(0, PORT_NUMBER, &info, &address);

	return address;
}

/// <summary>
/// Creates the listening socket
/// </summary>
/// <param name="address">The addrinfo for local address</param>
/// <returns>Listening socket</returns>
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

	freeaddrinfo(address);

	return sock;

}

/// <summary>
/// Assignes the listening socket
/// </summary>
/// <param name="socket">Socket to listen</param>
void ConnectionListen(SOCKET socket) {

	if (listen(socket, MAXLISTENERS) < 0) {
		fprintf(stderr, "Error: Listen failed\n");
		exit(1);
	}

}

/// <summary>
/// Connects to a client socket
/// </summary>
/// <param name="socket">Listening socket</param>
/// <returns>Client socket</returns>
SOCKET WaitAndConnect(SOCKET socket) {
	struct sockaddr_storage client_address;
	struct sockaddr* socket_address_client = (struct sockaddr*)&client_address;
	socklen_t length_of_client;
	SOCKET client_socket;
	char address_buffer[IP_ADDRESS_MAX];

	length_of_client = sizeof(client_address);

	client_socket = accept(socket, socket_address_client, &length_of_client);	//Accepts the first of the threeway handshake

	if (client_socket == INVALID_SOCKET) {
		fprintf(stderr, "Error: Accepted failed\n");
		exit(1);
	}

	getnameinfo(socket_address_client, length_of_client, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);

	printf("Client connected. Address : %s\n", address_buffer);

	return client_socket;
}

/// <summary>
/// Recieves a message from the socket
/// </summary>
/// <param name="message">Empty string</param>
/// <param name="target_socket">The socket to look for data</param>
/// <returns>The bytes recevied</returns>
int  ReceiveMessage(char message[], SOCKET target_socket) {

	int bytes_received = recv(target_socket, message, STRING_BUFFER, 0);

	printf("%.*s\n", bytes_received, message);

	return bytes_received;
}

/// <summary>
/// Responds to a request by sending a message
/// </summary>
/// <param name="message">Data string of the response</param>
/// <param name="target_socket">Socket for the intention of the message</param>
void RespondToClient(char message[], SOCKET target_socket) {

	int bytes_sent = send(target_socket, message, strlen(message), 0);

 }

/// <summary>
/// Closing a socket connection 
/// </summary>
/// <param name="socket">The socket to close</param>
void CloseSocketConnection(SOCKET socket) {

	closesocket(socket);

}

/// <summary>
/// Cleans up Windows sockets
/// </summary>
void WindowsSocketsCleanUp() {

	WSACleanup();
}
