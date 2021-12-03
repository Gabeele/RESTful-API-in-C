///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project

//Winsock includes
#define _CRT_SECURE_NO_WARNINGS
#pragma once

#define _WIN32_WINNT 0x6000

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

//Includes
#include <string.h>

//Defines 
#define IP_ADDRESS_MAX 16
#define PORT_NUMBER_MAX 4
#define STRING_BUFFER 250


typedef enum connection_type
{
	TCP, UDP

}connection_type;

void InitlaizeWindowsSockets();

struct addrinfo* ConfigureTargetAddress(char[], char[], connection_type);

SOCKET CreateConnectionToTargetSocket(struct addrinfo*);

void SendMessageToSocket(char[], SOCKET);

void ReceiveMessageFromSocket(char[], SOCKET);

void CloseSocketConnection(SOCKET);

void WindowsSocketsCleanUp();

void printTargetAddress(struct addrinfo*);