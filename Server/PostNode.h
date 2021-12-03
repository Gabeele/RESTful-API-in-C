#pragma once

#include "Posting.h"

typedef struct POSTNODE {
	p_Post data;
	p_Post next_node;

}*p_PostNode;

p_PostNode createNode(p_Post);



