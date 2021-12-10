///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
/// RestServices File on Server - Functions pertaining to REST actions, building responses, managing server data, and directing program flow

#include "RestServices.h"

/// <summary>
/// Parses the request, organizes the request, builds response and sends responses to client
/// </summary>
/// <param name="list">The list of postings</param>
/// <param name="client_socket">Client socket or intended recipiant</param>
/// <param name="payload">The request or message</param>
void parsePayloadAndAction(p_LISTOFPOSTINGS list, SOCKET client_socket, char payload[]) {

	//Payload Information
	char method[STRING_BUFFER];
	char path[STRING_BUFFER];
	char* body;
	
	//Payload data
	char keystr[STRING_BUFFER];
	int key;
	char author[STRING_BUFFER];
	char topic[STRING_BUFFER];
	char postBody[STRING_BUFFER];

	//Response to request
	char data[STRING_BUFFER];	
	char response[STRING_BUFFER];

	if (sscanf_s(payload, "%s %s HTTP/1.1\r\n", method, STRING_BUFFER, path, STRING_BUFFER) == EOF) {	//Obtains the method and path
		getResponseHeader(Not_Found, response);
		RespondToClient(response, client_socket);
		return;
	}

	body = strstr(payload, "\r\n\r\n");	//Obtains the body of the payload

	if (strcmp(method, "POST") == 0) {	//When the method is POST the system will add a new post to the linked list
		
		splitBody(body, author, topic, postBody);	

		if (post(list, author, topic, postBody) == 1) {	
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
		
		splitBody(body, author, topic, postBody);

		sscanf_s(path, "/posts/%d", &key);	//Obtains the path postingID

		if (put(list, key, author, topic, postBody) == 1) {
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
	else if (strcmp(method, "GET") == 0) {	//When the method is GET it will obtain the proper data determined through the path

		if (strstr(path, "/posts/")) {
			
			sscanf_s(path, "/posts/%s", keystr, STRING_BUFFER);	//Obtains the keyword

			stringDeformat(keystr);	
			
			if (sscanf_s(keystr, "%d", &key)== 1) {	//Checks if the keystr is a number

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
			else {	//If it is not a number 
				if (getFilter(list, keystr, data) == 1) {	//Get with a filter keyword
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
		else {	//If it is nether ID or keyword then retrive all the data
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
	else if (strcmp(method, "DELETE") == 0) {	//When the method is DELETE it will remove the posting with the ID
		sscanf_s(path, "/posts/%d", &key);

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
	else {	//If it is not any other the other methods, will respond with an error
		getResponseHeader(Not_Found, response);
		RespondToClient(response, client_socket);
	}

}

/// <summary>
/// Adds a posting to the list
/// </summary>
/// <param name="list">The list to add to</param>
/// <param name="author">Authors name</param>
/// <param name="topic">Topic of the subject</param>
/// <returns>Boolean integer if successful<</returns>
int post(p_LISTOFPOSTINGS list, char author[], char topic[], char postBody[]) {

	addToList(list, author, topic, postBody);

	return 1;
}

/// <summary>
/// Obtains all the postings information
/// </summary>
/// <param name="list">The list of postings</param>
/// <param name="data">Empty string to append the data to</param>
/// <returns>Boolean integer if successful<</returns>
int getAll(p_LISTOFPOSTINGS list, char data[])
{
	p_POSTNODE node = list->head;

	if (node == NULL) {
		return 0;
	}

	sprintf(data, "{\n");

	while (node != NULL) {

		sprintf(data + strlen(data), "\t{\"id\":\"%d\", \"author\":\"%s\", \"topic\":\"%s\", \"body\":\"%s\"}\n", getPostingID(node->data), getAuthor(node->data), getTopic(node->data), getBody(node->data));

		node = node->next_node;
	}

	sprintf(data + strlen(data), "}\n");

	return 1;
}

/// <summary>
/// Gets the data from a key
/// </summary>
/// <param name="list">List of postings</param>
/// <param name="key">The PostID key</param>
/// <param name="data">Empty string to append data to</param>
/// <returns>Boolean integer if successful</returns>
int get(p_LISTOFPOSTINGS list, int key, char data[]) {

	if (keyIsvalid(list, key) == 0) {
		return 0;
	}

	p_POSTNODE node = searchForNode(list, key);

	sprintf(data, "{\"id\":\"%d\", \"author\":\"%s\", \"topic\":\"%s\", \"body\":\"%s\"}\n", getPostingID(node->data), getAuthor(node->data), getTopic(node->data), getBody(node->data));

	return 1;
}

/// <summary>
/// Obtains the data from a list determined by a keyword
/// </summary>
/// <param name="list">The list of postings</param>
/// <param name="keyword">The keyword to search by</param>
/// <param name="data">Empty string to append data too</param>
/// <returns>Boolean integer if successful</returns>
int getFilter(p_LISTOFPOSTINGS list, char keyword[], char data[])
{
	int isFoundFlag = 0; //

	p_POSTNODE node = list->head;

	sprintf(data, "{\n");

	for (int i = 0; i < getLength(list); i++) {

		if (node == NULL) {
			break;
		}
		else if ((strstr(getAuthor(node->data), keyword) || (strstr(getTopic(node->data), keyword)) || (strstr(getBody(node->data), keyword)))) {
			
			sprintf(data + strlen(data), "\t{\"id\":\"%d\", \"author\":\"%s\", \"topic\":\"%s\", \"body\":\"%s\"}\n", getPostingID(node->data), getAuthor(node->data), getTopic(node->data), getBody(node->data));

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

/// <summary>
/// Updates a posting
/// </summary>
/// <param name="list">The list of postings</param>
/// <param name="key">PostingID of what to update</param>
/// <param name="author">New author</param>
/// <param name="topic">New Topic</param>
/// <returns>Boolean integer if successfu</returns>
int put(p_LISTOFPOSTINGS list, int key, char author[], char topic[], char postBody[]) {
	
	if (!keyIsvalid(list, key)) {
		return 0;
	}

	p_POSTNODE node = searchForNode(list, key);
	if (node == NULL) {
		return 0;        
	}

	setAuthor(&node->data, author);

	setTopic(&node->data, topic);

	setBody(&node->data, postBody);

	return 1;
}

/// <summary>
/// Deletes an item on the list by the key
/// </summary>
/// <param name="list">List of postings</param>
/// <param name="key">The PostID key</param>
/// <returns>Boolean integer if successful</returns>
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

/// <summary>
/// Splits the body of a request into anthor and topic
/// </summary>
/// <param name="body">The body of the request</param>
/// <param name="author">Empty author string</param>
/// <param name="topic">Empty topic string</param>
void splitBody(char body[], char author[], char topic[], char postBody[]) {

	int i = 0;

	while (i < strlen(body)) {	//Replaces the '&' with ' ' (Splits the string)
		if (body[i] == '&') {
			body[i] = ' ';
			
		}

		i++;
	}

	sscanf_s(body, "\r\n\r\nauthor=%s topic=%s postbody=%s", author, STRING_POST_MAX, topic, STRING_POST_MAX, postBody, STRING_POST_MAX);	//Sets the author and topic to char pointers

	stringDeformat(author);

	stringDeformat(topic);

	stringDeformat(postBody);

}

/// <summary>
/// Creates a header respones based on the code
/// </summary>
/// <param name="response_codes">Response code (Enumeration)</param>
/// <param name="response">Empty string to append</param>
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