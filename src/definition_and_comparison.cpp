#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "const_in_okinator.h"
#include "definition_and_comparison.h"

static okinator_error_t print_definition_node (node_t* target_node);
static okinator_error_t create_way            (node_t* node, way_t* ptr_way);
static okinator_error_t write_in_way          (way_t* ptr_way);
static okinator_error_t print_comparison      (way_t* ptr_way_1, way_t* ptr_way_2);

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
		print_definition_node (target_node -> parent);

		if ((target_node -> parent) -> right == target_node)
		{
			printf ("не ");
		}

		printf ("%s, ", (target_node -> parent) -> data);
	}

	return NOT_ERROR;
}

//---------------------------------------------------------------------------------------------------------------------------

static okinator_error_t create_way (node_t* node, way_t* ptr_way)
{
	assert (node);
	assert (ptr_way);
	assert (ptr_way -> target_str);

	ptr_way -> way_to_target_node = (node_t**) calloc (SIZE_WAY_TO_TARGET_NODE, sizeof (node_t*));
	if (ptr_way -> way_to_target_node == NULL) {printf ("%s:%d Not memory for calloc to way_to_target_node\n", __FILE__, __LINE__); return NOT_MEMORY_TARGET;}

	ptr_way -> index_on_way = 0;
	ptr_way -> size_way     = SIZE_WAY_TO_TARGET_NODE;

	find_position_node (node, ptr_way -> target_str, &(ptr_way -> target_node));

	okinator_error_t status = write_in_way (ptr_way);
	if (status != NOT_ERROR) {return status;}

	ptr_way -> index_on_way -= 1;

	return status;
}

static okinator_error_t write_in_way (way_t* ptr_way)
{
	assert (ptr_way);
	assert (ptr_way -> way_to_target_node);
	assert (ptr_way -> target_node);
	assert (ptr_way -> target_str);

	okinator_error_t status = NOT_ERROR;

	(ptr_way -> way_to_target_node)[ptr_way -> index_on_way] = ptr_way -> target_node;

	ptr_way -> index_on_way += 1;

	if (ptr_way -> index_on_way == ptr_way -> size_way)
	{
		ptr_way -> size_way *= 2;

		ptr_way -> way_to_target_node = (node_t**) realloc (ptr_way -> way_to_target_node, ptr_way -> size_way);
		if (ptr_way -> way_to_target_node == NULL) {printf ("%s:%d Not memory for realloc to way_to_target_node\n", __FILE__, __LINE__); return NOT_MEMORY_TARGET;}
	}

	if ((ptr_way -> target_node) -> parent != NULL)
	{
		(ptr_way -> target_node) = (ptr_way -> target_node) -> parent;

		status = write_in_way (ptr_way);
	}

	return status;
}


okinator_error_t compare_two_nodes (node_t* node, char* target_str_1, char* target_str_2)
{
	assert (node);
	assert (target_str_1);
	assert (target_str_2);

	okinator_error_t status = NOT_ERROR;

	way_t way_1 = {};
	way_t way_2 = {};

	way_1.target_str = target_str_1;
	way_2.target_str = target_str_2;

	create_way (node, &way_1);
	create_way (node, &way_2);

	print_comparison (&way_1, &way_2);

	free (way_1.way_to_target_node);
	free (way_2.way_to_target_node);

	return status;
}

static okinator_error_t print_comparison (way_t* ptr_way_1, way_t* ptr_way_2)
{
	assert (ptr_way_1);
	assert (ptr_way_2);
	assert (ptr_way_1 -> way_to_target_node);
	assert (ptr_way_2 -> way_to_target_node);
	assert (ptr_way_1 -> target_str);
	assert (ptr_way_2 -> target_str);

	printf ("%s и %s похожи тем, что они оба - ", ptr_way_1 -> target_str, ptr_way_2 -> target_str);

	while ((ptr_way_1 -> way_to_target_node)[(ptr_way_1 -> index_on_way) - 1] == (ptr_way_2 -> way_to_target_node)[(ptr_way_2 -> index_on_way) - 1])
	{
		if ((way_to_target_node_1[*ptr_index_on_way_1]) -> right == way_to_target_node_1[(*ptr_index_on_way_1) - 1])
		{
			printf ("не ");
		}

		printf ("%s, ", (way_to_target_node_1[*ptr_index_on_way_1]) -> data);

		*ptr_index_on_way_1 -= 1;
		*ptr_index_on_way_2 -= 1;
	}

	printf ("но %s - ", target_str_1);

	while (*ptr_index_on_way_1 > 0)
	{
		if ((way_to_target_node_1[*ptr_index_on_way_1]) -> right == way_to_target_node_1[(*ptr_index_on_way_1) - 1])
		{
			printf ("не ");
		}
		
		printf ("%s, ", (way_to_target_node_1[*ptr_index_on_way_1]) -> data);

		*ptr_index_on_way_1 -= 1;
	}

	printf ("а %s - ", target_str_2);

	while (*ptr_index_on_way_2 > 0)
	{
		if ((way_to_target_node_2[*ptr_index_on_way_2]) -> right == way_to_target_node_2[(*ptr_index_on_way_2) - 1])
		{
			printf ("не ");
		}

		printf ("%s, ", (way_to_target_node_2[*ptr_index_on_way_2]) -> data);

		*ptr_index_on_way_2 -= 1;
	}

	printf ("\n");

	return NOT_ERROR;
}
