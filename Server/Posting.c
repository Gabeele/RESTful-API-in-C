#include "Posting.h"


p_Post createPost(int id, char author[], char topic[]) {
	p_Post post = (p_Post)malloc(sizeof(p_Post));
	if (post == NULL) {
		exit(1);
	}

	post->postingID = id;

	strcpy_s(post->author, STRING_MAX, author);

	strcpy_s(post->topic, STRING_MAX, topic);
	
	return post;
}
