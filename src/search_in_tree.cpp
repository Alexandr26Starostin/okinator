#include <stdio.h>
#include <assert.h>

#include "const_in_okinator.h"
#include "new_node.h"
#include "search_in_tree.h"

char name_new_data[SIZE_NAME_NEW_DATA]  = "";
char name_left_data[SIZE_NAME_NEW_DATA] = "";

static okinator_error_t add_node_in_tree (node_t* node);

//---------------------------------------------------------------------------------------------------------------

okinator_error_t search_in_tree (node_t* node)
{
	assert (node);

	printf ("%s ?\n", node -> data);
	printf ("Y/n\n");

	char answer = '\0';
	scanf ("%c", &answer);

	printf ("\n");

	if ((answer == 'Y' || answer == 'y') && (getchar () == '\n'))
	{
		if (node -> left != NULL)
		{
			search_in_tree (node -> left);
		}
		else
		{
			printf ("Твой загаданный объект: %s\n", node -> data);
		}
	}

	else if ((answer == 'N' || answer == 'n') && (getchar () == '\n'))
	{
		if (node -> right != NULL)
		{
			search_in_tree (node -> right);
		}
		else
		{
			printf ("А что это было ?\n");

			add_node_in_tree (node);
		}
	}

	else 
	{
		while (getchar () != '\n') {}
		
		printf ("Я не смог понять твой ответ. Повтори, пожалуйста)))\n");

		search_in_tree (node);
	}

	return NOT_ERROR;
}

static okinator_error_t add_node_in_tree (node_t* node)
{
	assert (node);

	node -> right = attach_node (NULL, NULL, NULL, node, __LINE__, __FILE__);
	node -> left  = attach_node (NULL, NULL, NULL, node, __LINE__, __FILE__);

	scanf ("%[^'\n']", name_left_data);
	getchar ();
	(node -> left) -> data = name_left_data;

	printf ("\nЧем %s отличается от %s ?\n", (node -> left) -> data, node -> data);
	printf ("%s не...\n", node -> data);

	(node -> right) -> data = node -> data;

	scanf ("%[^'\n']", name_new_data);
	getchar ();
	node -> data = name_new_data;

	return NOT_ERROR;
}