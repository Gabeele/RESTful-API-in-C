#pragma once

#include "PostNode.h"


typedef struct listOfPostings {
	int maxID;
	struct POSTNODE* head;

}*p_LISTOFPOSTINGS, LISTOFPOSTINGS;

LISTOFPOSTINGS initalizeListOfPosts();

void addToList(p_LISTOFPOSTINGS, char[], char[]);

void deleteFromList(p_LISTOFPOSTINGS, int);

int getLength(p_LISTOFPOSTINGS);

p_POSTNODE searchForNode(p_LISTOFPOSTINGS, int);

void saveListToFile(p_LISTOFPOSTINGS);

LISTOFPOSTINGS readListFromFile();

int keyIsvalid(p_LISTOFPOSTINGS, int);

void stringDeformat(char[]);

void stringFormat(char[]);







