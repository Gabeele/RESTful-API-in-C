#include "PostingList.h"

LISTOFPOSTINGS initalizeListOfPosts() {

	LISTOFPOSTINGS list;

	list.head = NULL;

	list.maxID = 0;

	return list;
}

void addToList(p_LISTOFPOSTINGS list, char author[], char topic[]) {
	int id = ++list->maxID;

	POST posting = createPost(id, author, topic);

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

	free(nodeToDelete);	//Might have to make a delete for this
}

int getLength(p_LISTOFPOSTINGS list) {

	int counter = 0;
	p_POSTNODE currentNode = list->head;

	while (currentNode != NULL) {
		counter++;
		currentNode = currentNode->next_node;
	}

		return counter;
}

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

void saveListToFile(p_LISTOFPOSTINGS list) {
	FILE *filePointer;

	char tempAuthor[STRING_MAX], tempTopic[STRING_MAX];
	int tempPosting;

	fopen_s(&filePointer, "PostingList.txt", "w+");

	if (filePointer == NULL) {
		printf("Error: File creating and saving sensed an error");
		exit(1);
	}

	fprintf(filePointer, "%d\n", list->maxID);

	p_POSTNODE node = list->head;

	do{
	
		tempPosting = getPostingID(node->data);	//Set the temps to allow spaces in loading and saving
		strcpy(tempAuthor, getAuthor(node->data));
		strcpy(tempTopic, getTopic(node->data));

		stringFormat(tempAuthor);
		stringFormat(tempTopic);

		fprintf(filePointer, "%d %s %s\n", tempPosting, tempAuthor, tempTopic);
		
		node = node->next_node;

	} while (node != NULL);

	fclose(filePointer);
}




LISTOFPOSTINGS readListFromFile() {

	int tempID = 0;
	char tempAuthor[STRING_MAX];
	char tempTopic[STRING_MAX];
	char buf[STRING_MAX];

	LISTOFPOSTINGS list = initalizeListOfPosts();

	FILE* filePointer;
	fopen_s(&filePointer, "PostingList.txt", "r");

	if (filePointer == NULL) {
		printf("Error: File does not exists");
		return list;
	}

	fscanf_s(filePointer, "%d\n", &list.maxID);

	while (fscanf(filePointer, "%d %s %s\n", &tempID, tempAuthor, tempTopic) != EOF) {

		stringDeformat(tempAuthor);
		stringDeformat(tempTopic);

		POST post = createPost(tempID, tempAuthor, tempTopic);
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

//Helper functions 

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
