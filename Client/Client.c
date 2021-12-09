///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
///Client C File on Client - Functions for creating the network connection, building requests and displaying responses.

#include "Client.h"

/// <summary>
/// Inializes winsock on the system
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
/// Creates a addrinfo of a TCP connection.
/// </summary>
struct addrinfo* ConfigureTargetAddress(char ip[], char port[]) {
	
	ADDRINFO type_info;
	ADDRINFO *target_address;

	memset(&type_info, 0, sizeof(type_info)); 

		 type_info.ai_socktype = SOCK_STREAM;	//Using TCP for RESTful services

	 if (getaddrinfo(ip, port, &type_info, &target_address)) {
		 fprintf(stderr, "Error: Failed to configure target address\n");
		 exit(1);
	 }

	 return target_address;

}

/// <summary>
/// Creates a socket through a addrinfo stucture
/// </summary>
/// <param name="address">Addrinfo pointer</param>
/// <returns></returns>
SOCKET CreateConnectionToTargetSocket(struct addrinfo* address) {
	SOCKET sock;

	sock = socket(address->ai_family, address->ai_socktype, address->ai_protocol);	//Creates a socket based on the target address

	if (sock == INVALID_SOCKET) {
		fprintf(stderr, "Error: Failed to configure target socket\n");
		exit(1);
	}

	if (connect(sock, address->ai_addr, address->ai_addrlen)) {
		fprintf(stderr, "Error: Failed to connect target socket\n");
		exit(1);
	}

	freeaddrinfo(address);

	return sock;
}

/// <summary>
/// Sends a message to a selected socket
/// </summary>
/// <param name="message">The messages which is to be sent</param>
/// <param name="target_socket">The socket to send data to</param>
void SendMessageToSocket(char message[], SOCKET target_socket) {

	if (send(target_socket, message, strlen(message), 0) == 0) {
		printf("Error: Send failed on client side\n");
		exit(1);
	}

}

/// <summary>
/// Retrives a message from the targeted socket
/// </summary>
/// <param name="message">Blank string which will be recived</param>
/// <param name="target_socket">The socket to listen on</param>
/// <returns>Amount of bytes recieved</returns>
int ReceiveMessageFromSocket(char message[], SOCKET target_socket) {

	printf("Raw Data Response:\n");

	int bytes_received = recv(target_socket, message, STRING_BUFFER, 0);

	printf("%.*s", bytes_received, message);
	
	return bytes_received;
}

/// <summary>
/// Closes the socket
/// </summary>
/// <param name="socket">Socket to close</param>
void CloseSocketConnection(SOCKET socket) {

	closesocket(socket);

}

/// <summary>
/// Cleans up the windows sockets
/// </summary>
void WindowsSocketsCleanUp() {

	WSACleanup();
}

/// <summary>
/// Creates a post request
/// </summary>
/// <param name="request">Empty string where the reqest can eb appended</param>
/// <param name="author">Authors Name</param>
/// <param name="topic">Topic</param>
void buildPOSTRequest(char request[], char author[], char topic[]) {

	stringFormat(author);
	stringFormat(topic);

	sprintf(request, "POST /posts HTTP/1.1\r\n");
	sprintf(request + strlen(request), "Host: %s:%s\r\n", IP_ADDRESS, PORT_NUMBER);
	sprintf(request + strlen(request), "User-Agent: client.exe 1.0\r\n");
	sprintf(request + strlen(request), "\r\n\r\n");
	sprintf(request + strlen(request), "author=%s&topic=%s\r\n", author, topic);

}

/// <summary>
/// Create a get request
/// </summary>
/// <param name="request">Empty string where the request can be appended</param>
/// <param name="key">Posting ID for which posting to retrieve</param>
void buildGETRequest(char request[], int key) {

	sprintf(request, "GET /posts/%d HTTP/1.1\r\n", key);
	sprintf(request + strlen(request), "Host: %s:%s\r\n", IP_ADDRESS, PORT_NUMBER);
	sprintf(request + strlen(request), "User-Agent: client.exe 1.0\r\n");
	sprintf(request + strlen(request), "\r\n\r\n");

}

/// <summary>
/// Creates a get request
/// </summary>
/// <param name="request">Empty string where the request can be appended</param>
void buildGETCollectionRequest(char request[]) {

	sprintf(request, "GET /posts HTTP/1.1\r\n");
	sprintf(request + strlen(request), "Host: %s:%s\r\n", IP_ADDRESS, PORT_NUMBER);
	sprintf(request + strlen(request), "Connection: close\r\n");
	sprintf(request + strlen(request), "User-Agent: client.exe 1.0\r\n");
	sprintf(request + strlen(request), "\r\n\r\n");

}

/// <summary>
/// Creates a GET request 
/// </summary>
/// <param name="request">Empty string where the request can be appended</param>
/// <param name="key">Keyword for which posting to be obtained</param>
void buildGETFilterRequest(char request[], char keyword[])
{
	stringFormat(keyword);

	sprintf(request, "GET /posts/%s HTTP/1.1\r\n", keyword);
	sprintf(request + strlen(request), "Host: %s:%s\r\n", IP_ADDRESS, PORT_NUMBER);
	sprintf(request + strlen(request), "User-Agent: client.exe 1.0\r\n");
	sprintf(request + strlen(request), "\r\n\r\n");

}

/// <summary>
/// Creates an update request
/// </summary>
/// <param name="request">Empty string where the request can be appended</param>
/// <param name="author">A string of the updated authors name</param>
/// <param name="topic">A string of the updated topic</param>
/// <param name="key">Posting ID for which posting to be updated</param>
void buildPUTRequest(char request[], char author[], char topic[], int key) {

	stringFormat(author);
	stringFormat(topic);

	sprintf(request, "PUT /posts/%d HTTP/1.1\r\n", key);
	sprintf(request + strlen(request), "Host: %s:%s\r\n", IP_ADDRESS, PORT_NUMBER);
	sprintf(request + strlen(request), "User-Agent: client.exe 1.0\r\n");
	sprintf(request + strlen(request), "\r\n\r\n");
	sprintf(request + strlen(request), "author=%s&topic=%s\r\n", author, topic);

}

/// <summary>
/// Creates a delete request	
/// </summary>
/// <param name="request">Empty string where the request can be appended</param>
/// <param name="key">Posting ID for which posting to be deleted</param>
void buildDELETERequest(char request[], int key ) {

	sprintf(request, "DELETE /posts/%d HTTP/1.1\r\n", key);
	sprintf(request + strlen(request), "Host: %s:%s\r\n", IP_ADDRESS, PORT_NUMBER);
	sprintf(request + strlen(request), "User-Agent: client.exe 1.0\r\n");
	sprintf(request + strlen(request), "\r\n\r\n");

}

/// <summary>
/// Prints the address infomration 
/// </summary>
/// <param name="address">addrinfo pointer to an address</param>
void printTargetAddress(struct addrinfo* address) {

	char address_buff[STRING_BUFFER];
	char service_buff[STRING_BUFFER];

	getnameinfo(address->ai_addr, address->ai_addrlen, address_buff, sizeof(address_buff), service_buff, sizeof(service_buff), NI_NUMERICHOST);	//Sets the address and service information to a string

	printf("Server address is: %s\t%s\n", address_buff, service_buff);
}

/// <summary>
/// Formats string; swap '+' for ' '
/// </summary>
/// <param name="string">A string that include '+'</param>
void stringDeformat(char string[]) {

	int i = 0;
	while (i < strlen(string)) {
		if (string[i] == '+') {
			string[i] = ' ';
		}

		i++;
	}
}

/// <summary>
///Formats string; swap ' ' for '+'
/// </summary>
/// <param name="string">String in need of formating </param>
void stringFormat(char string[]) {

	int i = 0;
	while (i < strlen(string)) {
		if (string[i] == ' ') {
			string[i] = '+';
		}
		else if (string[i] == '\n') {
			string[strlen(string) - 1] = 0;	//Removes a new line character at the end of the string
		}

		i++;
	}
}


