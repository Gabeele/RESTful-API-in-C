///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
/// Posting header File on Server - Protoypes and definitions of a post structure
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRING_POST_MAX 256

typedef struct post {
	int postingID;
	char author[STRING_POST_MAX];
	char topic[STRING_POST_MAX];
	char body[STRING_POST_MAX];

}*p_POST, POST;

POST createPost(int, char[], char[], char[]);

int getPostingID(POST);

char* getAuthor(POST);

char* getTopic(POST);

char* getBody(POST);

void setAuthor(p_POST, char[]);

void setTopic(p_POST, char[]);

void setBody(p_POST, char[]);