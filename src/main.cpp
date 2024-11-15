#include <stdio.h>

#include "const_in_okinator.h"
#include "new_node.h"
#include "delete_tree.h"
#include "dump_tree.h"
#include "search_in_tree.h"
#include "definition_and_comparison.h"

int main ()
{
	char str_for_system[] = "dot okinator.dot -Tsvg -o pictures/okinator_0000.svg";
	size_t index          = 0;

	FILE* file_html = fopen ("okinator.html", "w");
	fprintf (file_html, "<pre>\n");

    char name_data_1[SIZE_NAME_NEW_DATA] = "Животное";
	node_t* node_1 = attach_node (name_data_1, NULL, NULL, NULL, __LINE__, __FILE__);
	if (node_1 == NULL) {delete_tree (node_1); printf ("Can't creat node_1\n"); return NOT_CREAT_NODE;}

	dump_tree (node_1, str_for_system, &index, file_html);

	char name_data_2[SIZE_NAME_NEW_DATA] = "Плавает";
	node_t* node_2 = attach_node (name_data_2, NULL, NULL, node_1, __LINE__, __FILE__);
	if (node_1 == NULL) {delete_tree (node_1); printf ("Can't creat node_2\n"); return NOT_CREAT_NODE;}

	char name_data_3[SIZE_NAME_NEW_DATA] = "Растение";
	node_t* node_3 = attach_node (name_data_3, NULL, NULL, node_1, __LINE__, __FILE__);
	if (node_1 == NULL) {delete_tree (node_1); printf ("Can't creat node_2\n"); return NOT_CREAT_NODE;}

	char name_data_4[SIZE_NAME_NEW_DATA] = "Кит";
	node_t* node_4 = attach_node (name_data_4, NULL, NULL, node_2, __LINE__, __FILE__);
	if (node_1 == NULL) {delete_tree (node_1); printf ("Can't creat node_1\n"); return NOT_CREAT_NODE;}

	char name_data_5[SIZE_NAME_NEW_DATA] = "Попугай";
	node_t* node_5 = attach_node (name_data_5, NULL, NULL, node_2, __LINE__, __FILE__);
	if (node_1 == NULL) {delete_tree (node_1); printf ("Can't creat node_1\n"); return NOT_CREAT_NODE;}

	char name_data_6[SIZE_NAME_NEW_DATA] = "Ромашка";
	node_t* node_6 = attach_node (name_data_6, NULL, NULL, node_3, __LINE__, __FILE__);
	if (node_1 == NULL) {delete_tree (node_1); printf ("Can't creat node_1\n"); return NOT_CREAT_NODE;}

	char name_data_7[SIZE_NAME_NEW_DATA] = "Гвоздь";
	node_t* node_7 = attach_node (name_data_7, NULL, NULL, node_3, __LINE__, __FILE__);
	if (node_1 == NULL) {delete_tree (node_1); printf ("Can't creat node_1\n"); return NOT_CREAT_NODE;}

	node_1 -> left  = node_2;
	node_1 -> right = node_3;

	node_2 -> left  = node_4;
	node_2 -> right = node_5;

	node_3 -> left  = node_6;
	node_3 -> right = node_7;

	dump_tree (node_1, str_for_system, &index, file_html);

	search_in_tree (node_1);

	dump_tree (node_1, str_for_system, &index, file_html);

	if (create_definition_node (node_1, name_data_5))
	{
		delete_tree (node_1);
		fclose (file_html);
	}

	if (create_definition_node (node_1, name_data_4))
	{
		delete_tree (node_1);
		fclose (file_html);
	}

	if (compare_two_nodes (node_1, name_data_5, name_data_4))
	{
		delete_tree (node_1);
		fclose (file_html);
	}

	fprintf (file_html, "</pre>\n");
	
	delete_tree (node_1);
	fclose (file_html);

	return NOT_ERROR;
}