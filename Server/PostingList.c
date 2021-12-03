#include "PostingList.h"

p_ListOfPostings initalizeListOfPosts() {

	p_ListOfPostings list = (p_ListOfPostings)malloc(sizeof(p_ListOfPostings));
	if (list == NULL) {
		exit(1);
	}

	list->head = NULL;

	list->maxID = 0;

	return list;
}

void addToList(p_ListOfPostings list, char author[], char topic[]) {

	p_Post posting = createPost(++list->maxID, author, topic);
	p_PostNode node = createNode(posting);

	if (list->head == NULL) {

		list->head = node;
	}
	else {
		p_PostNode currentNode = list->head;

		while (currentNode->next_node != NULL) {

			currentNode = currentNode->next_node;
		}

		currentNode->next_node = node;
	}

}

void deleteFromList(p_ListOfPostings list, int key) {

	p_PostNode nodeToDelete = searchForNode(list, key);

	if (nodeToDelete == list->head) {

		list->head = NULL;

	}
	else {

		p_PostNode currentNode = list->head;

		while (currentNode->next_node != nodeToDelete) {

			currentNode = currentNode->next_node;
		}

		currentNode->next_node = nodeToDelete->next_node;
		
	}

	free(nodeToDelete);	//Might have to make a delete for this
}

int getLength(p_ListOfPostings list) {

	int counter = 0;
	p_PostNode currentNode = list->head;

	while (currentNode->next_node != NULL) {
		counter++;
		currentNode = currentNode->next_node;
	}

		return counter;
}

p_PostNode searchForNode(p_ListOfPostings list, int key) {

	p_PostNode node = list->head;

	while (node->data->postingID != key) {
		
		node = node->next_node;
	}

	if (node->data->postingID == key) {
		return node;
	}
	else {
		return NULL;
	}

}


void saveListToFile(p_ListOfPostings list) {
	FILE *filePointer;

	filePointer = fopen_s(&filePointer, "PostingList.txt", "w");

	if (filePointer == NULL) {
		printf("Error: File creating and saving sensed an error");
		exit(1);
	}

	fprintf(filePointer, "%d\n", list->maxID);

	p_PostNode node = list->head;

	do{
	
		fprintf(filePointer, "%d %s %s\n", node->data->postingID, node->data->author, node->data->topic);
		
		node = node->next_node;

	} while (node != NULL);

	fclose(filePointer);
}

p_ListOfPostings readListFromFile() {

	int tempID = 0;
	char tempAuthor[STRING_MAX] = "";
	char tempTopic[STRING_MAX] = "";

	p_ListOfPostings list = initalizeListOfPosts();

	FILE* filePointer;
	filePointer = fopen( "PostingList.txt", "r");

	if (filePointer == NULL) {
		printf("Error: File does not exists");
		return list;
	}

	fscanf_s(filePointer, "%d\n", list->maxID);

	while (filePointer != EOF) {
		fscanf_s(filePointer, "%d %s %s\n", tempID, tempAuthor, tempTopic);

		p_Post post = createPost(tempID, tempAuthor, tempTopic);
		p_PostNode node = createNode(post);

		if (list->head == NULL) {
			list->head = node;
		}
		else {
			p_PostNode currentNode = list->head;

			while (currentNode->next_node != NULL) {

				currentNode = currentNode->next_node;
			}

			currentNode->next_node = node;
		}

	}
	
	fclose(filePointer);
	return list;
}

