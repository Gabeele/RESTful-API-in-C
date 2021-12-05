#pragma once

#include "Posting.h"

typedef struct postNode {
	struct post data;
	struct POSTNODE* next_node;

}*p_POSTNODE, POSTNODE;

p_POSTNODE createNode(Post);



