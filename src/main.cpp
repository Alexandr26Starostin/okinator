#include <stdio.h>

#include "const_in_okinator.h"
#include "new_node.h"
#include "delete_tree.h"
#include "dump_tree.h"

int main ()
{
	char str_for_system[] = "dot okinator.dot -Tpng -o pictures/okinator_0000.png";
	size_t index          = 0;

	FILE* file_html = fopen ("okinator.html", "w");
	fprintf (file_html, "<pre>\n");

	node_t* node_1 = attach_node ("Животное", NULL, NULL, NULL, __LINE__, __FILE__);
	if (node_1 == NULL) {delete_tree (node_1); printf ("Can't creat node_1\n"); return NOT_CREAT_NODE;}

	dump_tree (node_1, str_for_system, &index, file_html);

	node_t* node_2 = attach_node ("Котик", NULL, NULL, node_1, __LINE__, __FILE__);
	if (node_1 == NULL) {delete_tree (node_1); printf ("Can't creat node_2\n"); return NOT_CREAT_NODE;}

	node_t* node_3 = attach_node ("Не котик", NULL, NULL, node_1, __LINE__, __FILE__);
	if (node_1 == NULL) {delete_tree (node_1); printf ("Can't creat node_2\n"); return NOT_CREAT_NODE;}

	node_1 -> left  = node_2;
	node_1 -> right = node_3;

	dump_tree (node_1, str_for_system, &index, file_html);

	fprintf (file_html, "</pre>\n");
	
	delete_tree (node_1);
	fclose (file_html);

	return NOT_ERROR;
}