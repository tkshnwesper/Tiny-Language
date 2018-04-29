#include <string.h>
#include <stdlib.h>
#include "keywords.h"
#include "node.h"

NODE create_write_node(char* string) {
  NODE parent = allocate_node(), data = allocate_node();
  parent->data.node = data;
  parent->action = (keyword) write;
  parent->type = (node_type) action;
  char *string_heap = malloc(sizeof(char) * strlen(string) + 1);
  strcpy(string_heap, string);
  data->data.string = string_heap;
  data->action = (keyword) data;
  data->type = (node_type) string;
  return parent;
}
