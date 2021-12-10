///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
/// Posting C File on Server - Creates posting and getter/setter functions 

#include "Posting.h"

/// <summary>
/// Creates a posting structure
/// </summary>
/// <param name="id">Posting ID</param>
/// <param name="author">Author</param>
/// <param name="topic">Topic</param>
/// <param name="body">Body of the posting</param>
/// <returns>Non-pointer post</returns>
POST createPost(int id, char author[], char topic[], char body[]) {

	POST post;

	post.postingID = id;

	strcpy_s(post.author, STRING_POST_MAX, author);

	strcpy_s(post.topic, STRING_POST_MAX, topic);

	strcpy_s(post.body, STRING_POST_MAX, body);
	
	return post;
}

/// <summary>
/// Retrives the postingID
/// </summary>
/// <param name="post">Post</param>
/// <returns>Integer value of the ID</returns>
int getPostingID(POST post) {

	return post.postingID;
}

/// <summary>
/// Retrives the author of a post
/// </summary>
/// <param name="post">Post</param>
/// <returns>The pointer to the author</returns>
char* getAuthor(POST post) {

	return post.author;
}

/// <summary>
/// Retrives the topic of a post
/// </summary>
/// <param name="post">Post</param>
/// <returns>The pointer to the topic</returns>
char* getTopic(POST post) {

	return post.topic;
}

/// <summary>
/// Retrives the body of a post
/// </summary>
/// <param name="post">Post</param>
/// <returns>The pointer to the body</returns>
char* getBody(POST post) {
	return post.body;
}

/// <summary>
/// Sets the author
/// </summary>
/// <param name="post">Post to update</param>
/// <param name="author">New authors name</param>
void setAuthor(p_POST post, char author[]) {
	strcpy_s(post->author, STRING_POST_MAX,  author);

}

/// <summary>
/// Sets the topic 
/// </summary>
/// <param name="post">Post to update</param>
/// <param name="topic">New topic</param>
void setTopic(p_POST post, char topic[]) {
	strcpy_s(post->topic, STRING_POST_MAX, topic);

}

/// <summary>
/// Sets the body 
/// </summary>
/// <param name="post">Post to update</param>
/// <param name="topic">New body</param>
void setBody(p_POST post, char body[]) {
	strcpy_s(post->body, STRING_POST_MAX, body);

}

