///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project

#include <string.h>

#define IP_ADDRESS_MAX 16
#define PORT_NUMBER_MAX 4

typedef struct ADDRESS_INFO
{
	char target_ip_address[IP_ADDRESS_MAX];
	char target_port[PORT_NUMBER_MAX]

} *address_info_ptr;

 address_info_ptr* ConfigureTargetAddress(char[], char[]);