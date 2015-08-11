#include <stdio.h>
#include <stdlib.h>
#include "Library.h"
#include "Scanner.h"

int main() {
    TOKEN t = ReadFile("/home/saurabh/Code/Tiny/hello.t");
    printf("%s", t->next->name);
    return 0;
}
