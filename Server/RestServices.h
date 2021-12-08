#include "Server.h"
#include "PostingList.h"

#include <string.h>

enum response_codes
{
	OK = 200, Created = 201, Bad_Request = 400, Not_Found = 404
};

void parsePayloadAndAction(p_LISTOFPOSTINGS, SOCKET, char[]);

int post(p_LISTOFPOSTINGS list, char[], char[]); //Create

int getAll(p_LISTOFPOSTINGS, char[]);	//Get collection

int get(p_LISTOFPOSTINGS, int, char[]);	//Get post

int put(p_LISTOFPOSTINGS, int, char[], char[]);	//Update

int delete(p_LISTOFPOSTINGS, int);	//Delete

void stringDeformat(char[]);

void splitBody(char[], char[], char[]);

void getResponseHeader(int, char[]);