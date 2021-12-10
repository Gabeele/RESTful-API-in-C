///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
/// PostingList header File on Server - Defines the structure of the list and prototypes
#pragma once

#include "PostNode.h"

typedef struct listOfPostings {
	int maxID;	//Acts as a static counter for ID's. Only one instance of an ID can exists in a list
	struct POSTNODE* head;

}*p_LISTOFPOSTINGS, LISTOFPOSTINGS;

LISTOFPOSTINGS initalizeListOfPosts();

void addToList(p_LISTOFPOSTINGS, char[], char[]);

void deleteFromList(p_LISTOFPOSTINGS, int);

int getLength(p_LISTOFPOSTINGS);

p_POSTNODE searchForNode(p_LISTOFPOSTINGS, int);

p_POSTNODE searchByKeyword(p_LISTOFPOSTINGS, char[]);

void saveListToFile(p_LISTOFPOSTINGS);

LISTOFPOSTINGS readListFromFile();

int keyIsvalid(p_LISTOFPOSTINGS, int);

void stringDeformat(char[]);

void stringFormat(char[]);

void freeList(p_LISTOFPOSTINGS);


