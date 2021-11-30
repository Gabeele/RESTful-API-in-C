///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project

#include "Client.h"

 address_info_ptr* ConfigureTargetAddress(char ip[], char port[]) {
	
	 address_info_ptr ai;

	 strcpy_s(ai->target_ip_address, IP_ADDRESS_MAX, ip);

	 strcpy_s(ai->target_port, PORT_NUMBER_MAX, port);

	 return &ai;

}