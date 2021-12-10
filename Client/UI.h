///
///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
///UI header File on Client - Oragnizes and protoypes the UI

#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "Client.h"

#define INPUT_BUFFER 100
#define INPUT_BUFFER_POSTBODY 256
#define STRING_BUFFER 256

int menu(SOCKET);

void pressToContinute();

void printMenu();

void clearInputSteam();