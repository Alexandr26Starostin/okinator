#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "const_in_okinator.h"
#include "read_database.h"

static long len_file (FILE* file);

okinator_error_t read_database ()
{
	FILE* data_base = fopen ("database.txt", "r");

	long len_data_base = len_file (data_base);

	char* str_data_base = (char*) calloc (len_data_base + 1, sizeof (char));
	if (str_data_base == NULL) {printf ("%s:%d Not memory for str_data_base\n", __FILE__, __LINE__); fclose (data_base); return NOT_MEMORY_STR_DATA_BASE;}

	fread(str_data_base, sizeof (char), len_data_base, data_base);

	fclose (data_base);

	printf ("%s\n\n", str_data_base);

	char str_from_sscanf[MAX_LEN_STR_FROM_SSCANF] = "";

	size_t index_str = 0;

	char symbol = '\0';

	//int len_from_sscanf = 0;

	while (str_data_base[index_str] != '\0')
	{
		sscanf (str_data_base + index_str, "%c", &symbol);
		index_str += 1; 

		if (symbol == '\n' || symbol == '\t' || symbol == '}')
		{
			continue;
		}

		if (symbol == '{')
		{
			sscanf (str_data_base + index_str, "\"%[^\"]\"", str_from_sscanf);
			index_str += strlen(str_from_sscanf) + 2;  //+2 for \"

			printf ("%s\n", str_from_sscanf);
			
			continue;
		}
		
		printf ("Error in syntax in data_base\n Get wrong symbol: %c", symbol);
		printf ("\n%s\n", str_data_base + index_str - 1);
		return ERROR_IN_SYNTAX_DATA_BASE;
		
	}

	printf ("\n");

	free (str_data_base);

	return NOT_ERROR;
}

static long len_file (FILE* file)      
{ 
    assert (file);

    fseek (file, 0, SEEK_END);
    const long count_memory = ftell (file);
    fseek (file, 0, SEEK_SET);

    return count_memory;
}

