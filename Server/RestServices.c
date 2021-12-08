
#include "RestServices.h"


void parsePayloadAndAction(p_LISTOFPOSTINGS list, SOCKET client_socket, char payload[]) {

	//Payload Information
	char method[STRING_BUFFER];
	char path[STRING_BUFFER];
	char* body;
	
	//Payload data
	char keystr[STRING_BUFFER];
	int key;
	char  author[STRING_BUFFER];
	char topic[STRING_BUFFER];

	//Response to request
	char data[STRING_BUFFER];	
	char response[STRING_BUFFER];

	if (sscanf(payload, "%s %s HTTP/1.1\r\n", method, path) == EOF) {
		
		getResponseHeader(Not_Found, response);
		RespondToClient(response, client_socket);
		return;
	}

	body = strstr(payload, "\r\n\r\n");

	if (strcmp(method, "POST") == 0) {	//When the method is POST the system will add a new post to the linked list
		
		splitBody(body, author, topic);

		if (post(list, author, topic) == 1) {
			getResponseHeader(Created, response);
			RespondToClient(response, client_socket);
			return;
		}
		else {
			getResponseHeader(Bad_Request, response);
			RespondToClient(response, client_socket);
			return;
		}

	}
	else if (strcmp(method, "PUT") == 0) {	//When the method is PUT it will update the entry which was selected using the key
		
		splitBody(body, author, topic);

		sscanf(path, "/posts/%d", &key);

		if (put(list, key, author, topic) == 1) {
			getResponseHeader(OK, response);
			RespondToClient(response, client_socket);
			return;
		}
		else {
			getResponseHeader(Bad_Request, response);
			RespondToClient(response, client_socket);
			return;	
		}

	}
	else if (strcmp(method, "GET") == 0) {

		if (strstr(path, "/posts/")) {
			
			sscanf(path, "/posts/%s", keystr);

			stringDeformat(keystr);
			
			if (sscanf(keystr, "%d", &key)== 1) {	//Checks if the keystr is a number

				key = atoi(keystr);

				if (get(list, key, data) == 1) {	//Get with ID
					getResponseHeader(OK, response);
					sprintf(response + strlen(response), "%s", data);
					RespondToClient(response, client_socket);
					return;
				}
			
				else {
					getResponseHeader(Not_Found, response);
					RespondToClient(response, client_socket);
					return;
				}
			}
			else {
				if (getFilter(list, keystr, data) == 1) {	//Get with ID
					getResponseHeader(OK, response);
					sprintf(response + strlen(response), "%s", data);
					RespondToClient(response, client_socket);
					return;
				}

				else {
					getResponseHeader(Not_Found, response);
					RespondToClient(response, client_socket);
					return;
				}

			}
			
		}
		else {
			if (getAll(list, data) == 1) {
				getResponseHeader(OK, response);
				sprintf(response + strlen(response), "%s", data);
				RespondToClient(response, client_socket);
				return;
			}
			else {
				getResponseHeader(Not_Found, response);
				RespondToClient(response, client_socket);
				return;
			}

		}
		
	}
	else if (strcmp(method, "DELETE") == 0) {
		sscanf(path, "/posts/%d", &key);

		if (delete(list, key) == 1) {
			getResponseHeader(OK, response);
			RespondToClient(response, client_socket);
			return;
		}
		else {
			getResponseHeader(Not_Found, response);
			RespondToClient(response, client_socket);
		}
	}
	else {
		getResponseHeader(Not_Found, response);
		RespondToClient(response, client_socket);
	}

}

int post(p_LISTOFPOSTINGS list, char author[], char topic[]) {

	addToList(list, author, topic);

	return 1;
}

int getAll(p_LISTOFPOSTINGS list, char data[])
{
	p_POSTNODE node = list->head;

	if (node == NULL) {
		return 0;
	}

	sprintf(data, "{\n");

	while (node != NULL) {

		sprintf(data + strlen(data), "\t{\"id\":\"%d\", \"author\":\"%s\", \"topic\":\"%s\"}\n", getPostingID(node->data), getAuthor(node->data), getTopic(node->data));

		node = node->next_node;
	}

	sprintf(data + strlen(data), "}\n");

	return 1;
}

int get(p_LISTOFPOSTINGS list, int key, char data[]) {

	if (keyIsvalid(list, key) == 0) {
		return 0;
	}

	p_POSTNODE node = searchForNode(list, key);

	sprintf(data, "{\"id\":\"%d\", \"author\":\"%s\", \"topic\":\"%s\"}", getPostingID(node->data), getAuthor(node->data), getTopic(node->data));

	return 1;
}

int getFilter(p_LISTOFPOSTINGS list, char keyword[], char data[])
{
	int isFoundFlag = 0; //

	p_POSTNODE node = list->head;

	sprintf(data, "{\n");

	for (int i = 0; i < getLength(list); i++) {

		if (node == NULL) {
			break;
		}
		else if ((strstr(getAuthor(node->data), keyword) || (strstr(getTopic(node->data), keyword)))) {
			
			sprintf(data + strlen(data), "\t{\"id\":\"%d\", \"author\":\"%s\", \"topic\":\"%s\"}\n", getPostingID(node->data), getAuthor(node->data), getTopic(node->data));

			isFoundFlag = 1; 

		}

		node = node->next_node;
	}

	sprintf(data + strlen(data), "}\n");

	if (isFoundFlag) {
		return 1;
	}
	else {
		return 0;
	}

}

int put(p_LISTOFPOSTINGS list, int key, char author[], char topic[]) {
	
	if (!keyIsvalid(list, key)) {
		return 0;
	}

	p_POSTNODE node = searchForNode(list, key);
	if (node == NULL) {
		return 0;        
	}

	setAuthor(&node->data, author);

	setTopic(&node->data, topic);

	return 1;
}

int delete(p_LISTOFPOSTINGS list, int key) {

	if (!keyIsvalid(list, key)) {
		return 0;
	}

	p_POSTNODE node = searchForNode(list, key);		//Checks for the node to be in the list
	if (node == NULL) {
		return 0;
	}

	deleteFromList(list, key);

	return 1;
}


void splitBody(char body[], char author[], char topic[]) {

	int i = 0;

	while (i < strlen(body)) {	//Replaces the '&' with ' ' (Splits the string)
		if (body[i] == '&') {
			body[i] = ' ';
			break;
		}

		i++;
	}

	sscanf(body, "\r\n\r\nauthor=%s topic=%s", author, topic);	//Sets the author and topic to char pointers

	stringDeformat(author);

	stringDeformat(topic);

}

void getResponseHeader(int response_codes, char response[]) {
	
	switch (response_codes)
	{
	case OK:
		sprintf(response, "HTTP/1.1 200 OK\r\n\r\n");
		break;
	case Created:
		sprintf(response, "HTTP/1.1 201 Created\r\n\r\n");
		break;
	case Bad_Request:
		sprintf(response, "HTTP/1.1 400 Bad Request\r\n\r\n");
		break;
	case Not_Found:
		sprintf(response, "HTTP/1.1 404 Not Found\r\n\r\n");
		break;
	default:
		sprintf(response, "HTTP/1.1 404 Not Found\r\n\r\n");
		break;
	}

}