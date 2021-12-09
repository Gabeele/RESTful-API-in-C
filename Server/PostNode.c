///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
/// PostNode C File on Server - Functions to manage a post node
#include "PostNode.h"

/// <summary>
/// Creates a post node and asigns memory
/// </summary>
/// <param name="post">A post stucture</param>
/// <returns>A post node structure</returns>
p_POSTNODE createNode(POST post) {

	p_POSTNODE node = (p_POSTNODE)malloc(sizeof(POSTNODE));

	if (node == NULL) {
		exit(1);
	}

	node->data = post;
	node->next_node = NULL;

	return node;
}
