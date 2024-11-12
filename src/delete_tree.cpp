#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "const_in_okinator.h"
#include "delete_tree.h"

okinator_error_t delete_tree (node_t* ptr_node)
{
	assert (ptr_node);

	if ((ptr_node -> left) != NULL)
	{
		delete_tree (ptr_node -> left);
	}

	if ((ptr_node -> right) != NULL)
	{
		delete_tree (ptr_node -> right);
	}

	free (ptr_node);

	return NOT_ERROR;
}