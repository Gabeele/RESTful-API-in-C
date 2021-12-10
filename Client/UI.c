///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
///UI C File on Client - Interaction with the User and the system, prints menu, and other helper functions

#include "UI.h"

/// <summary>
/// Manages the user flow of the menu and directs the sending of requests
/// </summary>
/// <param name="target_socket">Targeted socket</param>
/// <returns>Integer (Boolean) for exiting the program</returns>
int menu(SOCKET target_socket) {
	int isRunning = 0; //boolean to exit the loop
	char option;

	do {
		
		isRunning = 0;

		char request[STRING_BUFFER];
		char author[INPUT_BUFFER];
		char topic[INPUT_BUFFER];
		char postBody[INPUT_BUFFER_POSTBODY];
		char keystr[INPUT_BUFFER];
		int key;

		system("cls");

		printMenu();

		printf("\nSelect menu option: ");

		option = getchar();

		switch (option) {
		case '1':	
			isRunning = 1;
			clearInputSteam();
			printf("\nTarget IP Address : %s\nTarget Port: %s\n", IP_ADDRESS, PORT_NUMBER);
			pressToContinute();
			break;
		case '2':	//POST
			clearInputSteam();

			printf("\nAuthor:  ");
			fgets(author, INPUT_BUFFER, stdin);

			printf("\nTopic: ");
			fgets(topic, INPUT_BUFFER, stdin);

			printf("\nPost Body (255 Character max): ");
			fgets(postBody, INPUT_BUFFER_POSTBODY, stdin);

			buildPOSTRequest(request, author, topic, postBody);
			SendMessageToSocket(request, target_socket);

			break;

		case '3':	//GET
			clearInputSteam();

			printf("\nKey:  ");
			fgets(keystr, INPUT_BUFFER, stdin);

			key = atoi(keystr);

			buildGETRequest(request, key);
			SendMessageToSocket(request, target_socket);
			break;
		case '4':	//GET Collection
			clearInputSteam();

			buildGETCollectionRequest(request);
			SendMessageToSocket(request, target_socket);
			break;
		case '5': //Put
			clearInputSteam();

			printf("\Key:  ");
			fgets(keystr, INPUT_BUFFER, stdin);
			key = atoi(keystr);

			printf("\nAuthor:  ");
			fgets(author, INPUT_BUFFER, stdin);


			printf("\nTopic: ");
			fgets(topic, INPUT_BUFFER, stdin);

			printf("\nPost Body (255 Character max): ");
			fgets(postBody, INPUT_BUFFER_POSTBODY, stdin);

			buildPUTRequest(request, author, topic, postBody, key);
			SendMessageToSocket(request, target_socket);
			break;
		case '6':	//Get Filter
			clearInputSteam();

			printf("\Keyword (Case-sensative):  ");
			fgets(keystr, INPUT_BUFFER, stdin);

			buildGETFilterRequest(request, keystr);
			SendMessageToSocket(request, target_socket);

			break;
		case '7':	//Delete 
			clearInputSteam();

			printf("\nKey:  ");
			fgets(keystr, INPUT_BUFFER, stdin);

			key = atoi(keystr);

			buildDELETERequest(request, key);
			SendMessageToSocket(request, target_socket);
			break;
		case 'x':

			return 1;	//Returns 1 (True) to close the connection
			break;
		default:
			isRunning = 1;
			break;
		}

	} while (isRunning);

		return 0;
}

/// <summary>
/// Helper function to pause user flow
/// </summary>
void pressToContinute() {

	printf("\nPress any key to continute...\n");

	getchar();
}

/// <summary>
/// Prints the menu
/// </summary>
void printMenu() {

	printf("Client-Server RESTful API Example\n");

	printf("\n\t[1] View Connection Info\n\t[2] Create a Post\n\t[3] Get a Post by Key\n\t[4] Get Collection of Posts\n\t[5] Update a Post\n\t[6] Get a Posts by Filter\n\t[7] Delete a Post by Key\n\t------------------------------\n\t[x] Exit and Disconnect\n");

}

/// <summary>
/// Clears the input stream of stdin of unwanted characters such as \n or \0
/// </summary>
void clearInputSteam() {
	char inputStreamCharacter;

	 do {
		inputStreamCharacter = getchar();

	 } while (inputStreamCharacter != '\n' && inputStreamCharacter != '\0');

}
