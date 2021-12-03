#include "UI.h"

void menu() {
	int isRunning = 1; //boolean to exit the loop
	char option;

	while (isRunning == 1) {
		system("cls");

		fflush(stdin);

		printMenu();

		printf("\nSelect menu option: ");

		option = getchar();
		switch (option) {
		case '1':
			//Single post
			break;
		case '2':
			//Collection post
			break;
		case '3':
			//Get
			break;
		case '4':
			//Get Collection
			break;
		case '5':
			//Put
			break;
		case '6':
			//Post
			break;
		case '7':
			//Delete
			break;
		case '8':
			//Get Filtering
			break;
		case 'x':
			return;
			break;
		default:
			break;
		}

	}

	
}

void printMenu() {

	printf("Client-Server RESTful API Example");

	printf("\n\t[1] Single Post\n\t[2] Collection Post\n\t[3] Get Single\n\t[4] Get Collection\n\t[5] Put\n\t[6] Post\n\t[7] Delete\n\n\t[x] Exit");

	//		 "\n[8] Get filtering
}
