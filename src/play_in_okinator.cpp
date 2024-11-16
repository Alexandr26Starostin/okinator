#include <stdio.h>
#include <assert.h>

#include "const_in_okinator.h"
#include "search_in_tree.h"
#include "definition_and_comparison.h"
#include "play_in_okinator.h"

okinator_error_t play_in_okinator (node_t* first_node)
{
	assert (first_node);

	okinator_error_t status = NOT_ERROR;

	printf ("1 - Я постараюсь отгадать загаданное тобой слово.\n"
			"2 - Я построю определение любого, известного мне слова.\n"
			"3 - Я сравню два любых, известных мне слова.\n"
			"4 - Я могу придти поиграть чуть позже)\n\n");

	printf ("...");

	long number_command = -1;

	scanf ("%ld", &number_command);

	char symbol = '\0';

	if ((symbol = (char) getchar ()) != '\n' || number_command < MIN_NUMBER_COMMAND || number_command > MAX_NUMBER_COMMAND)
	{
		while (symbol != '\n')
		{
			symbol = (char) getchar ();
		}
		
		printf ("Прости, из-за помех я не понял, о чём ты хотел меня попросить. Давай повторим.\n\n");
		
		status = play_in_okinator (first_node);
		return status;
	}

	printf ("\n\n");

	if (number_command == 1)
	{
		search_in_tree (first_node);

		printf ("\nПоиграем ещё?\n\n");

		status = play_in_okinator (first_node);
		return status;
	}

	if (number_command == 2)
	{
		char name_for_definition[SIZE_NAME_DEFINITION] = "";
		scanf ("%[^'\n']", name_for_definition);
		getchar ();

		create_definition_node (first_node, name_for_definition);

		printf ("\nПоиграем ещё?\n\n");

		status = play_in_okinator (first_node);
		return status;
	}

	if (number_command == 3)
	{
		char name_for_definition_1[SIZE_NAME_DEFINITION] = "";
		scanf ("%[^'\n']", name_for_definition_1);
		getchar ();
		

		char name_for_definition_2[SIZE_NAME_DEFINITION] = "";
		scanf ("%[^'\n']", name_for_definition_2);
		getchar ();

		if ((status = compare_two_nodes (first_node, name_for_definition_1, name_for_definition_2)) == NOT_MEMORY_TARGET)
		{
			return status;
		}

		printf ("\nПоиграем ещё?\n\n");

		status = play_in_okinator (first_node);
		return status;
	}

	if (number_command == 4)
	{
		return status;
	}

	return status;
}