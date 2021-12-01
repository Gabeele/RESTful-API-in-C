///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project

#include "Client.h"

struct addrinfo* ConfigureTargetAddress(char ip[], char port[], connection_type type) {
	
	ADDRINFO type_info;
	ADDRINFO *target_address;

	memset(&type_info, 0, sizeof(type_info));	//Create a container the size of addrinfo

	 if (type == TCP) {		//Sets the type of socket to TCP or UDP protocol
		 type_info.ai_socktype = SOCK_STREAM;
	 }
	 else if (type == UDP) {
		 type_info.ai_socktype = SOCK_DGRAM;
	 }
	 	 
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

	free(address);

	return sock;
}

//Printing Functions

void printTargetAddress(struct addrinfo* address) {

	char address_buff[STRING_BUFFER];
	char service_buff[STRING_BUFFER];

	getnameinfo(address->ai_addr, address->ai_addrlen, address_buff, sizeof(address_buff), service_buff, sizeof(service_buff), NI_NUMERICHOST);	//Sets the address and service information to a string

	printf("Target address is: %s\t%s\n", address_buff, service_buff);
}


