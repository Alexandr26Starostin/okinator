#ifndef DEFINITION_AND_COMPARISON_H
#define DEFINITION_AND_COMPARISON_H

okinator_error_t find_position_node     (node_t* node, char* target_str, node_t** ptr_target_node);
okinator_error_t create_definition_node (node_t* node, char* target_str);
okinator_error_t compare_two_nodes      (node_t* node, char* target_str_1, char* target_str_2);

#endif