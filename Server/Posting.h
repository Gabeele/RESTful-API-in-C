#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRING_MAX 250

typedef struct post {
	int postingID;
	char author[STRING_MAX];
	char topic[STRING_MAX];

}*p_POST, POST;

POST createPost(int, char[], char[]);

int getPostingID(POST);

char* getAuthor(POST);

char* getTopic(POST);