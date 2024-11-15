#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "const_in_okinator.h"
#include "dump_tree.h"

static okinator_error_t print_edge (node_t* node, FILE* file_okinator);

okinator_error_t dump_tree (node_t* node, char* str_for_system, size_t* ptr_index, FILE* file_html)
{
	assert (node);
	assert (str_for_system);
	assert (ptr_index);
	assert (file_html);

	FILE* file_okinator = fopen ("okinator.dot", "w");
	if (file_okinator == NULL) {printf ("Not find okinator.dot\n"); return NOT_FIND_OKINATOR_DOT;}

	fprintf (file_okinator, "digraph\n{\n\tnode[fontsize=9]\n\n\t");

	print_edge (node, file_okinator);

	fprintf (file_okinator, "}");

	fclose (file_okinator);

	system (str_for_system);

	fprintf (file_html, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"
						"<img src=\"pictures/okinator_%c%c%c%c.svg\" style=\"width: 100%%\">\n", 
						str_for_system[INDEX_NUMBER_OF_PICTURE + 0], str_for_system[INDEX_NUMBER_OF_PICTURE + 1], str_for_system[INDEX_NUMBER_OF_PICTURE + 2], str_for_system[INDEX_NUMBER_OF_PICTURE + 3]);

	*ptr_index += 1;
	size_t copy_index = *ptr_index;

	str_for_system[INDEX_NUMBER_OF_PICTURE + 0] = '0' + (char) (copy_index / 1000);
	copy_index                                 %= 1000;

	str_for_system[INDEX_NUMBER_OF_PICTURE + 1] = '0' + (char) (copy_index / 100);
	copy_index                                 %= 100;

	str_for_system[INDEX_NUMBER_OF_PICTURE + 2] = '0' + (char) (copy_index / 10);
	copy_index                                 %= 10;

	str_for_system[INDEX_NUMBER_OF_PICTURE + 3] = '0' + (char) (copy_index / 1);
	copy_index                                 %= 1;


	return NOT_ERROR;
}

static okinator_error_t print_edge (node_t* node, FILE* file_okinator)
{
	assert (node);
	assert (file_okinator);

	
	if (node -> parent != NULL)
	{
		fprintf (file_okinator, "node_%p [shape=record, label = \"{%s| {left = %p | node = %p | parent = %p | right = %p}}\" style=\"filled\",fillcolor=\"#BDEF9E\"]\n\n\t", node, node -> data,node -> left, node, node -> parent, node -> right);

		if ((node -> parent) -> left == node)
		{
			fprintf (file_okinator, "edge[color=\"red\",fontsize=12]\n\tnode_%p -> node_%p\n\n\t", node -> parent, node);
		}
		else
		{
			fprintf (file_okinator, "edge[color=\"blue\",fontsize=12]\n\tnode_%p -> node_%p\n\n\t", node -> parent, node);
		}
	}
	else
	{
		fprintf (file_okinator, "node_%p [shape=record, label = \"{%s| {left = %p | node = %p | parent = %p | right = %p}}\" style=\"filled\",fillcolor=\"yellow\"]\n\n\t", node, node -> data,node -> left, node, node -> parent, node -> right);
	}

	if (node -> left != NULL)
	{
		print_edge (node -> left, file_okinator);
	}

	if (node -> right != NULL)
	{
		print_edge (node -> right, file_okinator);
	}

	return NOT_ERROR;
}
