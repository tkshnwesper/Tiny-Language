#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "Library.h"

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

int isVariable(char* name) {
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
    else if(isVariable(name)) {
        return token_variable;
    }
    else if(isInteger(name)) {
        return token_integer;
    }
    else {
        printf("Unrecognized type \"%s\"", name);
        exit(1);
    }
}

TOKEN insert_token(TOKEN first, char* name) {
    TOKEN b, cur = first;

    if(first == NULL) {
        b = (TOKEN) malloc(sizeof(token));
        b->next = NULL;
        b->name = name;
        b->type = parse_type(name);
        return b;
    }

    while(cur->next != NULL) {
        cur = cur->next;
    }

    b = (TOKEN) malloc(sizeof(token));
    b->next = NULL;
    b->name = name;
    b->type = parse_type(name);
    cur->next = b;
    return first;
}
