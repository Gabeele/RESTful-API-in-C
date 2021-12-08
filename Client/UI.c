#include "UI.h"

int menu(SOCKET target_socket) {
	int isRunning = 0; //boolean to exit the loop
	char option;

	do {
		
		isRunning = 0;

		char request[STRING_BUFFER];
		char author[INPUT_BUFFER];
		char topic[INPUT_BUFFER];
		char keystr[INPUT_BUFFER];
		int key;

		system("cls");

		fflush(stdin);

		printMenu();

		printf("\nSelect menu option: ");

		option = getchar();


		switch (option) {
		case '1':
			//display connection info info
			break;
		case '2':	//POST
			clearInputSteam();

			printf("\nAuthor:  ");
			fgets(author, INPUT_BUFFER, stdin);


			printf("\nTopic: ");
			fgets(topic, INPUT_BUFFER, stdin);


			buildPOSTRequest(request, author, topic);
			SendMessageToSocket(request, target_socket);

			break;

		case '3':	//GET
			clearInputSteam();

			printf("\Key:  ");
			fgets(keystr, INPUT_BUFFER, stdin);

			key = atoi(keystr);

			buildGETRequest(request, key);
			SendMessageToSocket(request, target_socket);
			break;
		case '4':
			//Get Collection
			break;
		case '5':
			//Put
			break;
		case '6':
			//Delete
			break;
		case '7':
			//Get Filtering
			break;
		case 'x':

			return 1;
			break;
		default:
			isRunning = 1;
			break;
		}

	} while (isRunning);

		return 0;
}



void printMenu() {

	printf("Client-Server RESTful API Example");

	printf("\n\t[1] Single Post\n\t[2] Collection Post\n\t[3] Get Single\n\t[4] Get Collection\n\t[5] Put\n\t[6] Post\n\t[7] Delete\n\n\t[x] Exit");

	//		 "\n[8] Get filtering
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
