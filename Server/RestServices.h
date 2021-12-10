///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
/// RestServices header File on Server - Declaring variables, defines, and protoyping 

#include "Server.h"
#include "PostingList.h"

#include <ctype.h>
#include <string.h>

/// <summary>
/// Enumeration for the response codes
/// </summary>
enum response_codes
{
	OK = 200, Created = 201, Bad_Request = 400, Not_Found = 404
};

void parsePayloadAndAction(p_LISTOFPOSTINGS, SOCKET, char[]);

int post(p_LISTOFPOSTINGS, char[], char[], char[]); //Create

int getAll(p_LISTOFPOSTINGS, char[]);	//Get collection

int get(p_LISTOFPOSTINGS, int, char[]);	//Get post

int getFilter(p_LISTOFPOSTINGS, char[], char[]);

int put(p_LISTOFPOSTINGS, int, char[], char[], char[]);	//Update

int delete(p_LISTOFPOSTINGS, int);	//Delete

void stringDeformat(char[]);

void splitBody(char[], char[], char[], char[]);

void getResponseHeader(int, char[]);