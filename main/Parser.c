#include <stdio.h>
#include <stdlib.h>
#include "Library.h"

void ParseTokens(TOKEN t) {
    TOKEN raw, cur;

    while(t != NULL) {
        cur = raw = t;
        while(cur->next->type != token_terminator) {
            cur = cur->next;
        }
        t = cur->next->next;
        free(cur->next->name);
        free(cur->next);


    }
}
