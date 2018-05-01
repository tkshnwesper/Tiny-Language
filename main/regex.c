#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "regex.h"

#define ESCAPE_HANDLING_MECHANISM \
if (props->escape) {\
  escape_consequences(&props->escape, &props->escaped_character_count);\
  append_on_match(result, string, pattern[i], i, props);\
}

typedef struct properties {
  int paren_start;
  int paren_end;
  int escape;
  int dollar;
  int caret;
  int square_start;
  int square_end;
  int escaped_character_count;
  int square_count;
  int found_in_square;
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

void escape_consequences(int *escape, int *count) {
  if (*escape) {
    *escape = 0;
    (*count)++;
  }
}

int append_on_match(char **result, char *string, char letter, int i, PROPERTIES props) {
  if (string[
    i
    - props->paren_start
    - props->paren_end
    - props->escaped_character_count
    - props->square_count
    - props->square_end
  ] == letter) {
    *result = append_to_result(*result, letter);
    return 1;
  }
  return 0;
}

void loop_for_your_own_good(char *string, char *pattern, char **result, PROPERTIES props) {
  props->escaped_character_count = 0;
  props->found_in_square = 0;  
  props->square_count = 0;
  int pattern_len = strlen(pattern);
  for (int i = 0; i < pattern_len; i++) {
    int no_hope_left = 0;
    switch (pattern[i]) {
      case '\\': {
        ESCAPE_HANDLING_MECHANISM else {
          props->escape = 1;
        }
        break;
      }
      case '(': {
        ESCAPE_HANDLING_MECHANISM else {
          props->paren_start = 1;
        }
        break;
      }
      case ')': {
        ESCAPE_HANDLING_MECHANISM else {
          props->paren_end = 1;
        }
        break;
      }
      case '[': {
        ESCAPE_HANDLING_MECHANISM else {
          props->square_start++;
        }
        break;
      }
      case ']': {
        ESCAPE_HANDLING_MECHANISM else {
          props->square_end++;
          props->found_in_square = 0;
        }
        break;
      }
      default: {
        if (props->square_start != props->square_end) {
          if (props->found_in_square) {
            props->square_count++;
            break;
          }
          props->found_in_square = append_on_match(result, string, pattern[i], i, props);
          props->square_count++;
        }
        if (props->escape && i < pattern_len - 1) {
          *result = append_to_result(*result, pattern[i - 1]);
          props->escape = 0;
        }
        if (!append_on_match(result, string, pattern[i], i, props)) {
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
  props.square_start = 0;
  props.square_end = 0;
  props.escaped_character_count = 0;
  props.square_count = 0;
  props.found_in_square = 0;
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
    if (props.escape) return append_to_result(result, '$');
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
