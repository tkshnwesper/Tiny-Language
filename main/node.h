#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "tokens.h"

typedef enum node_type {
  string,
  number,
  action
} node_type;

typedef struct node {
  keyword action;
  union {
    int *integer;
    char *string;
    struct node *node;
  } data;
  node_type type;
} node, *NODE;

NODE allocate_node();

#endif
