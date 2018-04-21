#include <stdio.h>
#include <stdlib.h>
#include "Library.h"
#include "Scanner.h"

int main() {
    TOKEN cur, t = ReadFile("/home/saurabh/Code/Tiny/hello.t");
    cur = t;
    while(cur != NULL) {
        printf("%s%s", cur->trail, cur->name);
        cur = cur->next;
    }
    return 0;
}
