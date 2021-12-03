#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRING_MAX 250

typedef struct POST {
	int postingID;
	char author[STRING_MAX];
	char topic[STRING_MAX];

}*p_Post;

p_Post createPost(int, char[], char[]);


