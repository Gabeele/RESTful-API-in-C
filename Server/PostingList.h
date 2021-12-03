#pragma once

#include "PostNode.h"


typedef struct LISTOFPOSTINGS {
	int maxID;
	p_PostNode head;

}*p_ListOfPostings;

p_ListOfPostings initalizeListOfPosts();

void addToList(p_ListOfPostings, char[], char[]);

void deleteFromList(p_ListOfPostings);

int getLength(p_ListOfPostings);

p_PostNode searchForNode(p_ListOfPostings, int);

void saveListToFile(p_ListOfPostings);

p_ListOfPostings readListFromFile();





