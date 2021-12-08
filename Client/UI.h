#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "Client.h"

#define INPUT_BUFFER 100

int menu(SOCKET);

void pressToContinute();

void printMenu();

//void printConnection();

void clearInputSteam();