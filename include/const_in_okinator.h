#ifndef CONST_IN_OKINATOR_H
#define CONST_IN_OKINATOR_H

struct node_t 
{
	char*   data;
	node_t* left;
	node_t* right;
	node_t* parent;
};

enum okinator_error_t 
{
	NOT_ERROR                 = 0,
	NOT_MEMORY_FOR_NODE       = 1,
    NOT_CREAT_NODE            = 2,
	NOT_FIND_OKINATOR_DOT     = 3,
	NOT_MEMORY_TARGET         = 4,
	NOT_MEMORY_STR_DATA_BASE  = 5,
	ERROR_IN_SYNTAX_DATA_BASE = 6,
	NOT_FIND_TARGET           = 7
};

const size_t INDEX_NUMBER_OF_PICTURE   = 44;
const size_t SIZE_NAME_NEW_DATA        = 50;
const size_t SIZE_NAME_NEW_SIGN        = 50;
const size_t SIZE_NAME_DEFINITION      = 50;
const size_t SIZE_WAY_TO_TARGET_NODE   = 36;
const size_t MAX_LEN_STR_FROM_SSCANF   = 50;
const long   MIN_NUMBER_COMMAND        = 1;
const long   MAX_NUMBER_COMMAND        = 4;
const long   MIN_NUMBER_COMMAND_IN_ADD = 5;
const long   MAX_NUMBER_COMMAND_IN_ADD = 6;

struct way_t
{
	node_t** way_to_target_node;
	size_t   index_on_way;
	size_t   size_way;
	node_t*  target_node;
	char*    target_str;
};

#endif