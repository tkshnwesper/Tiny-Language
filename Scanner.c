#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Library.h"

TOKEN ReadFile(const char* filename) {

    BUF b = NULL, buft;
    TOKEN t = NULL, cur, temp_token;
    char *str;
    int count, i, c;
    FILE *f = fopen(filename, "r");

    if(f != NULL) {

        while((c = fgetc(f)) != EOF) {

            if(!isspace((char) c) && isalnum((char) c)) {
                b = insert_buffer(b, c);
            }

            else {
                // special character
                if(!isalnum((char) c) && !isspace((char) c)) {
                    str = (char *) malloc(sizeof(char) * 2);
                    str[0] = (char) c;
                    str[1] = '\0';
                    t = insert_token(t, str);
                }

                if(b != NULL) {
                    count = 0;
                    buft = b;
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
                    t = insert_token(t, str);
                    free(b);
                    b = NULL;
                }
            }

        }

    }

    else {
        printf("There was a problem with opening the file.\n");
        exit(1);
    }

    fclose(f);

    // corrections

    cur = t;
    // handles ":=" operator
    while(cur->next != NULL) {
        if(strcmp(cur->name, ":") == 0 && strcmp(cur->next->name, "=") == 0) {
            temp_token = cur->next->next;
            free(cur->next->name);
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
