#pragma once

#define _WIN32_WINNT 0x6000

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

//Includes
#include <string.h>

#define IP_ADDRESS_MAX 16
#define PORT_NUMBER_MAX 4
#define STRING_BUFFER 100
#define MAXLISTENERS 10

typedef enum connection_type
{
	TCP, UDP

}connection_type;

struct addrinfo* ConfigureLocalAddress();

SOCKET CreateListeningSocket(struct addrinfo*);

void ConnectionListen(SOCKET);