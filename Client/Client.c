///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project

#include "Client.h"

void InitlaizeWindowsSockets() {

	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data))
	{
		fprintf(stderr, "Error: Failed to initialize\n");
		exit(1);
	}

}

struct addrinfo* ConfigureTargetAddress(char ip[], char port[]) {
	
	ADDRINFO type_info;
	ADDRINFO *target_address;

	memset(&type_info, 0, sizeof(type_info)); 

		 type_info.ai_socktype = SOCK_STREAM;	//Using TCP for RESTful services

	 if (getaddrinfo(ip, port, &type_info, &target_address)) {
		 fprintf(stderr, "Error: Failed to configure target address\n");
		 exit(1);
	 }

	 printTargetAddress(target_address);

	 return target_address;

}

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

void SendMessageToSocket(char message[], SOCKET target_socket) {

	if (send(target_socket, message, strlen(message), 0) == 0) {
		printf("Error: Send failed on client side\n");
		exit(1);
	}

}

int ReceiveMessageFromSocket(char message[], SOCKET target_socket) {

	int bytes_received = recv(target_socket, message, STRING_BUFFER, 0);


	printf("%.*s", bytes_received, message);
	
	return bytes_received;
}

void CloseSocketConnection(SOCKET socket) {

	closesocket(socket);

}

void WindowsSocketsCleanUp() {

	WSACleanup();
}

void buildPOSTRequest(char request[], char author[], char topic[]) {

	stringFormat(author);
	stringFormat(topic);

	sprintf(request, "POST /posts HTTP/1.1\r\n");
	sprintf(request + strlen(request), "Host: %s:%s\r\n", IP_ADDRESS, PORT_NUMBER);
	sprintf(request + strlen(request), "Connection: close\r\n");
	sprintf(request + strlen(request), "User-Agent: client.exe 1.0\r\n");
	sprintf(request + strlen(request), "\r\n\r\n");
	sprintf(request + strlen(request), "author=%s&topic=%s\r\n", author, topic);

}

void buildGETRequest(char request[], int key) {

	sprintf(request, "GET /posts/%d HTTP/1.1\r\n", key);
	sprintf(request + strlen(request), "Host: %s:%s\r\n", IP_ADDRESS, PORT_NUMBER);
	sprintf(request + strlen(request), "Connection: close\r\n");
	sprintf(request + strlen(request), "User-Agent: client.exe 1.0\r\n");
	sprintf(request + strlen(request), "\r\n\r\n");

}

void buildGETCollectionRequest(char request[]) {

	sprintf(request, "GET /posts HTTP/1.1\r\n");
	sprintf(request + strlen(request), "Host: %s:%s\r\n", IP_ADDRESS, PORT_NUMBER);
	sprintf(request + strlen(request), "Connection: close\r\n");
	sprintf(request + strlen(request), "User-Agent: client.exe 1.0\r\n");
	sprintf(request + strlen(request), "\r\n\r\n");

}

void buildPUTRequest(char request[], char author[], char topic[], int key) {

	stringFormat(author);
	stringFormat(topic);

	sprintf(request, "PUT /posts/%d HTTP/1.1\r\n", key);
	sprintf(request + strlen(request), "Host: %s:%s\r\n", IP_ADDRESS, PORT_NUMBER);
	sprintf(request + strlen(request), "Connection: close\r\n");
	sprintf(request + strlen(request), "User-Agent: client.exe 1.0\r\n");
	sprintf(request + strlen(request), "\r\n\r\n");
	sprintf(request + strlen(request), "author=%s&topic=%s\r\n", author, topic);

}

void buildDELETERequest(char request[], int key ) {

	sprintf(request, "DELETE /posts/%d HTTP/1.1\r\n", key);
	sprintf(request + strlen(request), "Host: %s:%s\r\n", IP_ADDRESS, PORT_NUMBER);
	sprintf(request + strlen(request), "Connection: close\r\n");
	sprintf(request + strlen(request), "User-Agent: client.exe 1.0\r\n");
	sprintf(request + strlen(request), "\r\n\r\n");

}


//Printing Functions

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


