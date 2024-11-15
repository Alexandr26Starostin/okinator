#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "const_in_okinator.h"
#include "new_node.h"

//static okinator_error_t find_position_node (node_t* ptr_new_node, node_t* ptr_parent);

static okinator_error_t creat_new_node (node_t** ptr_ptr_node, int line, const char* file);

//----------------------------------------------------------------------------------------------------------------------

node_t* attach_node (char* str_name, node_t* ptr_left, node_t* ptr_right, node_t* ptr_parent, int line, const char* file)
{
	assert (file);

	node_t* ptr_new_node = NULL;

	creat_new_node (&ptr_new_node, line, file);
	if (ptr_new_node == NULL) {return ptr_new_node;}

	ptr_new_node -> data   = str_name;
	ptr_new_node -> right  = ptr_right;
	ptr_new_node -> left   = ptr_left;
	ptr_new_node -> parent = ptr_parent;

	return ptr_new_node;
}

static okinator_error_t creat_new_node (node_t** ptr_ptr_node, int line, const char* file)
{
	assert (file);   
	assert (ptr_ptr_node);

	*ptr_ptr_node = (node_t*) calloc (1, sizeof (node_t));
	if (ptr_ptr_node == NULL)
	{
		printf ("Error in %s:%d\nName memory: NOT_MEMORY_FOR_NODE\n calloc return NULL in file: creat_new_node.cpp\n", file, line);
		return NOT_MEMORY_FOR_NODE;
	}

	return NOT_ERROR;
}
