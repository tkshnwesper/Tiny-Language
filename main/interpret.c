#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "keywords.h"

void* interpret(char* string) {
  if (strlen(string) == 0) {
    return NULL;
  }
  // char *token = strtok(string, " ");
  return create_write_node(string);
}