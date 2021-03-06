///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
///Client header File on Client - Oragnizes and protoypes the client file

#define _CRT_SECURE_NO_WARNINGS

#pragma once

#define _WIN32_WINNT 0x6000

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

//Defines 
#define IP_ADDRESS_MAX 16
#define PORT_NUMBER_MAX 4
#define STRING_BUFFER 2048
#define IP_ADDRESS "127.0.0.1"
#define PORT_NUMBER "8080"

void InitlaizeWindowsSockets();

struct addrinfo* ConfigureTargetAddress(char[], char[]);

SOCKET CreateConnectionToTargetSocket(struct addrinfo*);

void SendMessageToSocket(char[], SOCKET);

int ReceiveMessageFromSocket(char[], SOCKET);

void CloseSocketConnection(SOCKET);

void WindowsSocketsCleanUp();

void buildPOSTRequest(char[], char[], char[], char[]);

void buildGETRequest(char[], int);

void buildGETCollectionRequest(char[]);

void buildGETFilterRequest(char[], char[]);

void buildPUTRequest(char[], char[], char[], char[], int);

void buildDELETERequest(char[], int);

void printTargetAddress(struct addrinfo*);

void stringFormat(char[]);

void stringDeformat(char[]);