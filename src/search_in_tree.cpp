#include <stdio.h>
#include <assert.h>

#include "const_in_okinator.h"
#include "new_node.h"
#include "search_in_tree.h"

char name_new_data[SIZE_NAME_NEW_DATA]  = "";
char name_left_data[SIZE_NAME_NEW_DATA] = "";

static okinator_error_t add_node_in_tree        (node_t* node);
static okinator_error_t add_node_in_data_base   (node_t* first_node);
static okinator_error_t write_tree_in_data_base (node_t* node, FILE* data_base);

//---------------------------------------------------------------------------------------------------------------

okinator_error_t search_in_tree (node_t* node, node_t* first_node)
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
			search_in_tree (node -> left, first_node);
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
			search_in_tree (node -> right, first_node);
		}
		else
		{
			printf ("А что это было ?\n");

			add_node_in_tree (node);

			add_node_in_data_base (first_node);
		}
	}

	else 
	{
		while (getchar () != '\n') {}
		
		printf ("Я не смог понять твой ответ. Повтори, пожалуйста)))\n");

		search_in_tree (node, first_node);
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

static okinator_error_t add_node_in_data_base (node_t* first_node)
{
	assert (first_node);

	okinator_error_t status = NOT_ERROR;

	printf ("\nОчень интересно) Как мне поступить ?)\n"
					"5 - Я могу запомнить твой рассказ, и в следующий я смогу отгадать это слово.\n"
					"6 - Я могу подыграть тебе и сделать вид, что я не помню это слово.\n\n");
	
	long number_command = -1;

	scanf ("%ld", &number_command);

	char symbol = '\0';

	if ((symbol = (char) getchar ()) != '\n' || number_command < MIN_NUMBER_COMMAND_IN_ADD || number_command > MAX_NUMBER_COMMAND_IN_ADD)
	{
		while (symbol != '\n')
		{
			symbol = (char) getchar ();
		}
		
		printf ("Прости, из-за помех я не понял, о чём ты хотел меня попросить. Давай повторим.\n\n");
		
		status = add_node_in_data_base (first_node);
		return status;
	}

	if (number_command == 5)
	{
		FILE* data_base = fopen ("database.txt", "w");

		write_tree_in_data_base (first_node, data_base);
		
		fclose (data_base);
	}

	return NOT_ERROR;
}

static okinator_error_t write_tree_in_data_base (node_t* node, FILE* data_base)
{
	assert (node);
	assert (data_base);

	fprintf (data_base, "{\"%s\"", node -> data);

	if (node -> left != NULL)
	{
		write_tree_in_data_base (node -> left, data_base);
	}

	if (node -> right != NULL)
	{
		write_tree_in_data_base (node -> right, data_base);
	}
	
	fprintf (data_base, "}");

	return NOT_ERROR;
}