#include "PostNode.h"

p_PostNode createNode(p_Post post) {

	p_PostNode node = (p_PostNode)malloc(sizeof(p_PostNode));
	if (node == NULL) {
		exit(1);
	}

	node->data = post;
	node->next_node = NULL;

	return node;
}
