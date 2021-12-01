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



	 return target_address;

}


