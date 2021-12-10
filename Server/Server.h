///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
/// Server header File on Server - Declaring variables, defines, and protoyping 


//#define _CRT_SECURE_NO_WARNINGS
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
#define IP_ADDRESS "127.0.0.1"
#define PORT_NUMBER "8080"
#define STRING_BUFFER 2048	//Large number so data from browsers and command lines do not fill the buffer
#define MAXLISTENERS 10

typedef enum connection_type
{
	TCP, UDP

}connection_type;

void InitlaizeWindowsSockets();

struct addrinfo* ConfigureLocalAddress();

SOCKET CreateListeningSocket(struct addrinfo*);

void ConnectionListen(SOCKET);

SOCKET WaitAndConnect(SOCKET);

void CloseSocketConnection(SOCKET);

void WindowsSocketsCleanUp();

int ReceiveMessage(char[], SOCKET);

void RespondToClient(char[], SOCKET);