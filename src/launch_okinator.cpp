#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "const_in_okinator.h"
#include "new_node.h"
#include "delete_tree.h"
#include "launch_okinator.h"
#include "dump_tree.h"
#include "play_in_okinator.h"

static long len_file (FILE* file);

static okinator_error_t create_tree   (char* str_data_base, long* ptr_index_str, char* ptr_symbol, node_t* node);
static okinator_error_t read_database (char* str_data_base, FILE* data_base);

okinator_error_t launch_okinator ()
{
	okinator_error_t status = NOT_ERROR;

	FILE* data_base = fopen ("database.txt", "r");

	long len_data_base = len_file (data_base);

	char* str_data_base = (char*) calloc (len_data_base *5, sizeof (char));  //+1 for '\0'
	if (str_data_base == NULL) {printf ("%s:%d Not memory for str_data_base\n", __FILE__, __LINE__); fclose (data_base); return NOT_MEMORY_STR_DATA_BASE;}

	read_database (str_data_base, data_base);

	//-----------------------------------------------------------------------------------
	
	char symbol        = '\0';
	long index_str     = 0;
	node_t* first_node = attach_node (NULL, NULL, NULL, NULL, __LINE__, __FILE__);

	create_tree (str_data_base, &index_str, &symbol, first_node);

	//-----------------------------------------------------------------------------------

	char str_for_system[] = "dot okinator.dot -Tsvg -o pictures/okinator_0000.svg";
	size_t index_picture  = 0;

	FILE* file_html = fopen ("okinator.html", "w");
	fprintf (file_html, "<pre>\n");

	dump_tree (first_node, str_for_system, &index_picture, file_html);

	//----------------------------------------------------------------------------------

	printf ("\nПривет!!! Я Окинатор! Не хочешь поиграть?\n\n");

	if ((status = play_in_okinator (first_node)) == NOT_MEMORY_TARGET)
	{
		fclose      (file_html);
		delete_tree (first_node);
		free        (str_data_base);

		return status;
	}

	//----------------------------------------------------------------------------------

	fprintf (file_html, "</pre>\n");
	
	fclose      (file_html);
	delete_tree (first_node);
	free        (str_data_base);

	return status;
}

//-------------------------------------------------------------------------------------------------------------------------------------

static long len_file (FILE* file)      
{ 
    assert (file);

    fseek (file, 0, SEEK_END);
    const long count_memory = ftell (file);
    fseek (file, 0, SEEK_SET);

    return count_memory;
}

static okinator_error_t read_database (char* str_data_base, FILE* data_base)
{
	assert (str_data_base);
	assert (data_base);

	char symbol    = '\0';
	long index_str = 0;

	while ((symbol = (char) fgetc (data_base)) != EOF)
	{
		if (symbol == '\n' || symbol == '\t')
		{
			continue;
		}

		if (symbol == '"')
		{
			symbol = (char) fgetc (data_base);

			if (symbol == '\n' || symbol == '}' || symbol == '{')
			{
				str_data_base[index_str++] = '\0';
			}

			str_data_base[index_str++] = '"';

			if (symbol != '\n')
			{
				str_data_base[index_str++] = symbol;
			}

			continue;
		}

		str_data_base[index_str++] = symbol;
	}

	str_data_base[index_str] = '\n';
	fclose (data_base);

	for (int i = 0; i < index_str; i++)
	{
	printf ("%c", str_data_base[i]);
	}

	//printf ("\n\n%s\n\n", str_data_base);

	return NOT_ERROR;
}

static okinator_error_t create_tree (char* str_data_base, long* ptr_index_str, char* ptr_symbol, node_t* node)
{
	assert (str_data_base);
	assert (ptr_index_str);
	assert (ptr_symbol);
	assert (node);

	if (str_data_base[*ptr_index_str] == '\n')
	{
		return NOT_ERROR;
	}

	//printf ("%c\n", str_data_base[*ptr_index_str]);
	*ptr_index_str += 2;   //+2 for {"

	node -> data = str_data_base + *ptr_index_str;
	//printf ("%s\n", node -> data);
 	*ptr_index_str += strlen(node -> data) + 2;  //+2 for \0"

	//printf ("%c\n", str_data_base[*ptr_index_str]);

	if (str_data_base[*ptr_index_str] == '{')
	{
		node -> left = attach_node (NULL, NULL, NULL, node, __LINE__, __FILE__);
		create_tree (str_data_base, ptr_index_str, ptr_symbol, node -> left);

		node -> right = attach_node (NULL, NULL, NULL, node, __LINE__, __FILE__);
		create_tree (str_data_base, ptr_index_str, ptr_symbol, node -> right);
	}

	if (str_data_base[*ptr_index_str] == '}')
	{
		*ptr_index_str += 1;
		return NOT_ERROR;
	}

	return NOT_ERROR;
}
