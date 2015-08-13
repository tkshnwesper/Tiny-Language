#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "Library.h"

char* buffer_to_string(BUF b) {
    BUF buft = b;
    char *str;
    int i, count = 0;
    if(b == NULL) {
        str = (char *) malloc(sizeof(char));
        str[0] = '\0';
        return str;
    }
    while(buft != NULL) {
        count++;
        buft = buft->next;
    }
    str = (char *) malloc(sizeof(char) * count + 1);
    buft = b;
    for(i = 0; i < count; i++) {
        str[i] = (char) buft->value;
        buft = buft->next;
    }
    str[count] = '\0';
    return str;
}

void free_buffer(BUF b) {
    BUF t;
    while(b != NULL) {
        t = b;
        b = b->next;
        free(t);
    }
}

BUF insert_buffer(BUF first, int val) {
    BUF b, cur = first;

    if(first == NULL) {
        b = (BUF) malloc(sizeof(buffer));
        b->next = NULL;
        b->value = val;
        return b;
    }

    while(cur->next != NULL) {
        cur = cur->next;
    }

    b = (BUF) malloc(sizeof(buffer));
    b->next = NULL;
    b->value = val;
    cur->next = b;
    return first;
}

int compare_all(char *str, char **test, int n) {
    int i;
    for(i = 0; i < n; i++) {
        if(strcmp(str, test[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isInteger(char* name) {
    int len = strlen(name);
    int i;
    for(i = 0; i < len; i++) {
        if(!isdigit(name[i])) {
            return 0;
        }
    }
    return 1;
}

int isString(char* name) {
    int i;
    int len = strlen(name);
    if(isdigit(name[0])) {
        return 0;
    }
    for(i = 0; i < len; i++) {
        if(!isalnum(name[i])) {
            return 0;
        }
    }
    return 1;
}

int isArithmatic(char* name) {
    char* arithmatic[] = {
        "+",
        "-",
        "*",
        "/"
    };
    return compare_all(name, arithmatic, 4);
}

int isLogical(char* name) {
    char* logical[] = {
        "=",
        "<",
        ">"
    };
    return compare_all(name, logical, 3);
}

token_type parse_type(char* name) {

    if(isArithmatic((name))) {
        return token_arithmatic;
    }
    else if(isLogical(name)) {
        return token_logical;
    }
    else if(strcmp(name, ";") == 0) {
        return token_terminator;
    }
    else if(strcmp(name, ":") == 0) {
        return token_none;
    }
    else if(isString(name)) {
        return token_string;
    }
    else if(isInteger(name)) {
        return token_integer;
    }
    else {
        printf("Unrecognized type \"%s\"", name);
        exit(1);
    }
}

TOKEN insert_token(TOKEN first, char* name, char* trail) {
    TOKEN b, cur = first;

    if(first == NULL) {
        b = (TOKEN) malloc(sizeof(token));
        b->next = NULL;
        b->name = name;
        b->type = parse_type(name);
        b->trail = trail;
        return b;
    }

    while(cur->next != NULL) {
        cur = cur->next;
    }

    b = (TOKEN) malloc(sizeof(token));
    b->next = NULL;
    b->name = name;
    b->type = parse_type(name);
    b->trail = trail;
    cur->next = b;
    return first;
}
