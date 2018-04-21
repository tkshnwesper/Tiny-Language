#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

typedef enum token_type {
//    token_keyword,
    token_arithmatic,
    token_logical,
    token_string,
    token_integer,
//    token_string,
    token_terminator,
    token_assignment,
    token_none
} token_type;

// a container for tokens (in general)

typedef struct token {
    char* name;
    char* trail;
    struct token* next;
    token_type type;
} token, *TOKEN;

// a container for a variable

typedef struct var {
    int value;
    char type;
} var, *VAR;

typedef struct buffer {
    int value;
    struct buffer* next;
} buffer, *BUF;

typedef enum node_type {
    node_variable,
    node_integer,
    // logical
    node_equal,
    node_greater,
    node_lesser,
    // arithmatic
    node_add,
    node_subtract,
    node_multiply,
    node_divide,
    // assignment
    node_assignment
} node_type;

typedef struct node {
    struct node* next;
} node, *NODE;

typedef struct tree {
    struct tree* next;
    NODE root;
} tree, *TREE;

void free_buffer(BUF);

char* buffer_to_string(BUF);

BUF insert_buffer(BUF first, int val);

TOKEN insert_token(TOKEN first, char* name, char* trail);

#endif // LIBRARY_H_INCLUDED
