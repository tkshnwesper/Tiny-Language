#include <string.h>
#include "regex.h"

char *match(char *string, char *pattern) {
  if (string == NULL) return NULL;
  if (pattern == NULL) return "";
  if (strlen(string) == 0) {
    return "";
  }
  return pattern;
}