#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "regex.h"

typedef struct properties {
  int paren_start;
  int paren_end;
  int escape;
  int dollar;
  int caret;
} properties, *PROPERTIES;

char *append_to_result(char *result, char appendee) {
  if (result != NULL) {
    int len = strlen(result);
    char *new_result = (char *) malloc(len + 2);
    new_result[len + 1] = '\0';
    strcpy(new_result, result);
    new_result[len] = appendee;
    free(result);
    return new_result;
  }
  char *new_result = (char *) malloc(2);
  new_result[1] = '\0';
  new_result[0] = appendee;
  return new_result;
}

void escape_consequences(int *escape) {
  if (*escape) {
    *escape = 0;
  }
}

int append_on_match(char **result, char *string, char letter, int i, PROPERTIES props, int count) {
  if (string[i - props->paren_start - props->paren_end - count] == letter) {
    *result = append_to_result(*result, letter);
    return 1;
  }
  return 0;
}

void loop_for_your_own_good(char *string, char *pattern, char **result, PROPERTIES props) {
  int escaped_character_count = 0;
  for (int i = 0; i < strlen(pattern); i++) {
    int no_hope_left = 0;
    switch (pattern[i]) {
      case '\\':
        props->escape = 1;
        escaped_character_count++;
        break;
      case '(': {
        if (props->escape) {
          escape_consequences(&props->escape);
          append_on_match(result, string, pattern[i], i, props, escaped_character_count);
        } else {
          props->paren_start = 1;
        }
        break;
      }
      case ')': {
        if (props->escape) {
          escape_consequences(&props->escape);
          append_on_match(result, string, pattern[i], i, props, escaped_character_count);
        } else {
          props->paren_end = 1;
        }
        break;
      }
      default: {
        if (!append_on_match(result, string, pattern[i], i, props, escaped_character_count)) {
          no_hope_left = 1;
          if (*result != NULL) {
            free(*result);
            *result = NULL;
          }
          break;
        }
      }
    }
    if (no_hope_left) break;
  }
}

char *match(char *string, char *pattern) {
  if (string == NULL || strlen(string) == 0 || pattern == NULL) return NULL;
  char *result = NULL;
  properties props;
  props.paren_start = 0;
  props.paren_end = 0;
  props.escape = 0;
  props.dollar = pattern[strlen(pattern) - 1] == '$';
  props.caret = pattern[0] == '^';
  if (props.dollar) {
    char *dup = strdup(pattern);
    dup[strlen(dup) - 1] = '\0';
    pattern = dup;
  }
  if (props.caret) {
    pattern = pattern + 1;
    loop_for_your_own_good(string, pattern, &result, &props);
  } else {
    char *partial = string;
    do {
      loop_for_your_own_good(partial, pattern, &result, &props);
      if (result != NULL) break;
    } while (*(++partial) != '\0');
  }
  if (result != NULL && props.dollar) {
    char *partial = string;
    int verified = 0;
    while(partial != '\0' && (partial = strstr(partial, result)) != NULL) {
      if (partial[strlen(result)] == '\0') {
        verified = 1;
        break;
      }
      ++partial;
    }
    return verified ? result : NULL;
  }
  return result;
}
