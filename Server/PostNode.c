#include "PostNode.h"

p_POSTNODE createNode(POST post) {

	p_POSTNODE node = (p_POSTNODE)malloc(sizeof(POSTNODE));

	if (node == NULL) {
		exit(1);
	}

	node->data = post;
	node->next_node = NULL;

	return node;
}
