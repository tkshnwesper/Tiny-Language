#include <stdlib.h>
#include "node.h"

typedef struct node_list {
  NODE node;
  struct node_list *next;
} node_list, *NODE_LIST;

NODE_LIST allocated_node_list = NULL;

void insert_into_node_list(NODE_LIST new_node_list) {
  if (allocated_node_list == NULL) {
    allocated_node_list = new_node_list;
  } else {
    NODE_LIST node_list_iterator = allocated_node_list;
    while(node_list_iterator->next != NULL) node_list_iterator = node_list_iterator->next;
    node_list_iterator->next = new_node_list;
  }
}

void allocate_node_list(NODE new_node) {
  NODE_LIST new_node_list = (NODE_LIST) malloc(sizeof(node_list));
  new_node_list->next = NULL;
  new_node_list->node = new_node;
  insert_into_node_list(new_node_list);
}

NODE allocate_node() {
  NODE new_node = (NODE) malloc(sizeof(node));
  new_node->data.string = NULL;
  new_node->data.integer = NULL;
  new_node->data.node = NULL;
  allocate_node_list(new_node);
  return new_node;
}

