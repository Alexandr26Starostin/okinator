#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "const_in_okinator.h"
#include "definition_and_comparison.h"

static okinator_error_t print_definition_node (node_t* target_node);

//---------------------------------------------------------------------------------------------------------------------------

okinator_error_t find_position_node (node_t* node, char* target_str, node_t** ptr_target_node)
{
	assert (node);
	assert (ptr_target_node);
	assert (target_str);

	if (*ptr_target_node == NULL)
	{
		if (strcmp(node -> data, target_str) == 0)
		{
			*ptr_target_node = node;
		}
		else
		{
			if (node -> left != NULL)
			{
				find_position_node (node -> left, target_str, ptr_target_node);
			}

			if (node -> right != NULL)
			{
				find_position_node (node -> right, target_str, ptr_target_node);
			}
		}
	}

	return NOT_ERROR;
}

//---------------------------------------------------------------------------------------------------------------------------

okinator_error_t create_definition_node (node_t* node, char* target_str)
{
	assert (node);
	assert (target_str);

	node_t* target_node = NULL;

	find_position_node (node, target_str, &target_node);

	printf ("%s - ", target_str);

	print_definition_node (target_node);

	printf ("\n");

	return NOT_ERROR;
}

static okinator_error_t print_definition_node (node_t* target_node)
{
	assert (target_node);

	if (target_node -> parent != NULL)
	{
		if ((target_node -> parent) -> right == target_node)
		{
			printf ("не ");
		}

		printf ("%s, ", (target_node -> parent) -> data);

		print_definition_node (target_node -> parent);
	}

	return NOT_ERROR;
}

//---------------------------------------------------------------------------------------------------------------------------

okinator_error_t compare_two_nodes (node_t* node, char* target_str_1, char* target_str_2)
{
	assert (node);
	assert (target_str_1);
	assert (target_str_2);

	node_t* target_node_1 = NULL;
	node_t* target_node_2 = NULL;

	find_position_node (node, target_str_1, &target_node_1);
	find_position_node (node, target_str_2, &target_node_2);
}