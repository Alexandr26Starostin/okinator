#ifndef CONST_IN_OKINATOR_H
#define CONST_IN_OKINATOR_H

struct node_t 
{
	const char* data;
	node_t*     left;
	node_t*     right;
	node_t*     parent;
};

enum okinator_error_t 
{
	NOT_ERROR             = 0,
	NOT_MEMORY_FOR_NODE   = 1,
    NOT_CREAT_NODE        = 2,
	NOT_FIND_OKINATOR_DOT = 3
};

const size_t INDEX_NUMBER_OF_PICTURE = 44;

#endif