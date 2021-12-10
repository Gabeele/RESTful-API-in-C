///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
/// PostingList C File on Server - Creates, manages, the list and list items. Included is helper functions
#include "PostingList.h"

/// <summary>
/// Creates an empty list
/// </summary>
/// <returns>A non-pointer list</returns>
LISTOFPOSTINGS initalizeListOfPosts() {

	LISTOFPOSTINGS list;

	list.head = NULL;

	list.maxID = 0;

	return list;
}

/// <summary>
/// Adds an item to a list
/// </summary>
/// <param name="list">The list to add</param>
/// <param name="author">String of authors name</param>
/// <param name="topic">String of topic</param>
void addToList(p_LISTOFPOSTINGS list, char author[], char topic[], char body[]) {
	int id = ++list->maxID;

	POST posting = createPost(id, author, topic, body);

	p_POSTNODE node = createNode(posting);

	if (list->head == NULL) {

		list->head = node;
	}
	else {
		p_POSTNODE currentNode = list->head;

		while (currentNode->next_node != NULL) {

			currentNode = currentNode->next_node;
		}

		currentNode->next_node = node;
	}

}

/// <summary>
/// Removes an item from list
/// </summary>
/// <param name="list">List to remove something from</param>
/// <param name="key">The postingID to remove by</param>
void deleteFromList(p_LISTOFPOSTINGS list, int key) {

	p_POSTNODE nodeToDelete = searchForNode(list, key);

	p_POSTNODE currentNode = list->head;

	if (nodeToDelete == currentNode) {

		if (currentNode->next_node != NULL) {

			list->head = currentNode->next_node;

		}
		else {

			list->head = NULL;

		}
		
	}
	else {

		while (currentNode->next_node != nodeToDelete) {

			currentNode = currentNode->next_node;
		}

		currentNode->next_node = nodeToDelete->next_node;
		
	}

	freeNode(currentNode);
}

/// <summary>
/// Obtains the length of the list
/// </summary>
/// <param name="list">List of postings</param>
/// <returns>The numerical amount of items in the list</returns>
int getLength(p_LISTOFPOSTINGS list) {

	int counter = 0;
	p_POSTNODE currentNode = list->head;

	while (currentNode != NULL) {
		counter++;
		currentNode = currentNode->next_node;
	}

		return counter;
}

/// <summary>
/// Searh for a node through a key
/// </summary>
/// <param name="list">The list to search</param>
/// <param name="key">The postingID to search by</param>
/// <returns>A pointer to a node</returns>
p_POSTNODE searchForNode(p_LISTOFPOSTINGS list, int key) {

	p_POSTNODE node = list->head;

	while (getPostingID(node->data) != key) {
		
		node = node->next_node;
	}

	if (getPostingID(node->data) == key) {
		return node;
	}
	else {
		return NULL;
	}

}

/// <summary>
/// Save the list to a file
/// </summary>
/// <param name="list">The list to save</param>
void saveListToFile(p_LISTOFPOSTINGS list) {
	FILE *filePointer;

	char tempAuthor[STRING_POST_MAX], tempTopic[STRING_POST_MAX], tempBody[STRING_POST_MAX];
	int tempPosting;

	fopen_s(&filePointer, "PostingList.txt", "w+");

	if (filePointer == NULL) {
		printf("Error: File creating and saving sensed an error\n");
		exit(1);
	}

	fprintf(filePointer, "%d\n", list->maxID);

	p_POSTNODE node = list->head;

	do{
	
		tempPosting = getPostingID(node->data);	//Set the temps to allow spaces in loading and saving
		strcpy_s(tempAuthor, STRING_POST_MAX, getAuthor(node->data));
		strcpy_s(tempTopic, STRING_POST_MAX, getTopic(node->data));
		strcpy_s(tempBody, STRING_POST_MAX, getBody(node->data));

		stringFormat(tempAuthor);
		stringFormat(tempTopic);
		stringFormat(tempBody);

		fprintf(filePointer, "%d %s %s %s\n", tempPosting, tempAuthor, tempTopic, tempBody);
		
		node = node->next_node;


	} while (node != NULL);

	fclose(filePointer);
}

/// <summary>
/// Reads and creates a list from a file location
/// </summary>
/// <returns>A non-pointer list</returns>
LISTOFPOSTINGS readListFromFile() {

	int tempID = 0;
	char tempAuthor[STRING_POST_MAX];
	char tempTopic[STRING_POST_MAX];
	char tempBody[STRING_POST_MAX];
	char buf[STRING_POST_MAX];

	LISTOFPOSTINGS list = initalizeListOfPosts();	

	FILE* filePointer;
	fopen_s(&filePointer, "PostingList.txt", "r");

	if (filePointer == NULL) {
		printf("Error: File does not exists. Creating a file...\n\n");
		return list;	//Returns the empty list if there isn't a file
	}

	fscanf_s(filePointer, "%d\n", &list.maxID);

	while (fscanf(filePointer, "%d %s %s %s\n", &tempID, tempAuthor, tempTopic, tempBody) != EOF) {

		stringDeformat(tempAuthor);
		stringDeformat(tempTopic);
		stringDeformat(tempBody);

		POST post = createPost(tempID, tempAuthor, tempTopic, tempBody);
		p_POSTNODE node = createNode(post);

		if (list.head == NULL) {
			list.head = node;
		}
		else {
			p_POSTNODE currentNode = list.head;

			while (currentNode->next_node != NULL) {

				currentNode = currentNode->next_node;
			}

			currentNode->next_node = node;
		}

	}
	


	fclose(filePointer);
	return list;
}

/// <summary>
/// Frees the list from memory
/// </summary>
/// <param name="list">List to be freed</param>
void freeList(p_LISTOFPOSTINGS list) {

	p_POSTNODE currentNode = list->head;
	p_POSTNODE previousNode = list->head;

	while (currentNode != NULL) {

		previousNode = currentNode;

		currentNode = currentNode->next_node;

		freeNode(previousNode);

	}

}


//Helper functions 

/// <summary>
/// Check if a key is valid in the lsit
/// </summary>
/// <param name="list">List to search</param>
/// <param name="key">The key to validate</param>
/// <returns>Integer boolean if it was sucessful</returns>
int keyIsvalid(p_LISTOFPOSTINGS list, int key) {
	int validFlag = 0;	//0 = false, flag to ensure it is true

	p_POSTNODE node = list->head;

	for (int i = 0; i < getLength(list); i++) {
		
		if (node == NULL && !validFlag) {
			return 0;
		}
		else if (key == getPostingID(node->data)) {
			return 1;
		}

		node = node->next_node;
	}

	return 0;
}

/// <summary>
/// Formats string; swap '+' for ' '
/// </summary>
/// <param name="string">A string that include '+'</param>
void stringDeformat(char string[]) {

	int i = 0;
	while (i < strlen(string)) {
		if (string[i] == '+') {
			string[i] = ' ';
		}

		i++;
	}
}

/// <summary>
///Formats string; swap ' ' for '+'
/// </summary>
/// <param name="string">String in need of formating </param>
void stringFormat(char string[]) {

	int i = 0;
	while (i < strlen(string)) {
		if (string[i] == ' ') {
			string[i] = '+';
		}

		i++;
	}
}
