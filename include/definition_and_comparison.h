#ifndef DEFINITION_AND_COMPARISON_H
#define DEFINITION_AND_COMPARISON_H

okinator_error_t find_position_node     (node_t* node, char* target_str, node_t** ptr_target_node);
okinator_error_t create_definition_node (node_t* node, char* target_str);

#endif