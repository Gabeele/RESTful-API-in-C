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
/// <returns></returns>
POST createPost(int id, char author[], char topic[]) {

	POST post;

	post.postingID = id;

	strcpy_s(post.author, STRING_POST_MAX, author);

	strcpy_s(post.topic, STRING_POST_MAX, topic);
	
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
