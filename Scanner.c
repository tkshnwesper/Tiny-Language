#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Library.h"

TOKEN ReadFile(const char* filename) {

    BUF b = NULL, trailbuf = NULL;
    TOKEN t = NULL, cur, temp_token;
    char *str, *trail = NULL;
    int c;
    FILE *f = fopen(filename, "r");

    if(f != NULL) {

        while((c = fgetc(f)) != EOF) {
            if(isalnum(c)) {
                if(trailbuf != NULL) {
                    trail = buffer_to_string(trailbuf);
                    free_buffer(trailbuf);
                    trailbuf = NULL;
                }
                b = insert_buffer(b, c);
            }
            // special character
            else if(!isalpha(c) && !isspace(c)) {
                if(trail != NULL) {
                    str = buffer_to_string(b);
                    free_buffer(b);
                    b = NULL;
                    t = insert_token(t, str, trail);
                    trail = NULL;
                }
                trail = buffer_to_string(trailbuf);
                free_buffer(trailbuf);
                trailbuf = NULL;
                str = (char *) malloc(sizeof(char) * 2);
                str[0] = (char) c;
                str[1] = '\0';
                t = insert_token(t, str, trail);
                trail = NULL;

            }
            // whitespace
            else {
                if(b != NULL) {
                    if(trail == NULL) {
                        trail = buffer_to_string(trailbuf);
                        free_buffer(trailbuf);
                        trailbuf = NULL;
                    }
                    str = buffer_to_string(b);
                    free_buffer(b);
                    b = NULL;
                    t = insert_token(t, str, trail);
                    trail = NULL;
                }
                trailbuf = insert_buffer(trailbuf, c);
            }
        }

    }

    else {
        printf("There was a problem with opening the file.\n");
        exit(1);
    }

    // handles characters remaining in buffer
    if(b != NULL) {
        trail = buffer_to_string(trailbuf);
        free_buffer(trailbuf);
        trailbuf = NULL;
        str = buffer_to_string(b);
        free_buffer(b);
        b = NULL;
        t = insert_token(t, str, trail);
    }

    fclose(f);

    // corrections

    cur = t;
    // handles ":=" operator
    while(cur->next != NULL) {
        if(strcmp(cur->name, ":") == 0 && strcmp(cur->next->name, "=") == 0) {
            temp_token = cur->next->next;
            free(cur->next->name);
            free(cur->next->trail);
            free(cur->next);
            cur->type = token_assignment;
            free(cur->name);
            cur->name = (char *) malloc(sizeof(char) * 3);
            strcpy(cur->name, ":=");
            cur->next = temp_token;
        }
        cur = cur->next;
    }

    return t;

}
