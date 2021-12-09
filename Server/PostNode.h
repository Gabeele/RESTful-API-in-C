///CSCN72020 - Computer Networks Assignment 3 
///RESTful API in C
///
///Gavin Abeele - gabeele2160@conestogac.on.ca
/// 
///v1.0 - December 1st, 2021: Inital project
/// 
/// PostNode header File on Server - Defines a post node for a linked list and the prototypes
#pragma once

#include "Posting.h"

typedef struct postNode {
	struct post data;
	struct POSTNODE* next_node;

}*p_POSTNODE, POSTNODE;

p_POSTNODE createNode(Post);



