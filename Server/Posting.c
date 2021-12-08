#include "Posting.h"


POST createPost(int id, char author[], char topic[]) {

	POST post;

	post.postingID = id;

	strcpy_s(post.author, STRING_MAX, author);

	strcpy_s(post.topic, STRING_MAX, topic);
	
	return post;
}

int getPostingID(POST post) {

	return post.postingID;
}

char* getAuthor(POST post) {

	return post.author;
}

char* getTopic(POST post) {

	return post.topic;
}

void setAuthor(p_POST post, char author[]) {
	strcpy(post->author, author);

}

void setTopic(p_POST post, char topic[]) {
	strcpy(post->topic, topic);

}
