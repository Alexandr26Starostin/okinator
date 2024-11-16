#include <stdio.h>

#include "const_in_okinator.h"
#include "search_in_tree.h"
#include "definition_and_comparison.h"
#include "launch_okinator.h"

//Проверка файлов на открытие

int main ()
{
	okinator_error_t status = NOT_ERROR;

	if ((status = launch_okinator ()) != NOT_ERROR) 
	{
		return status;
	}

	return status;
}