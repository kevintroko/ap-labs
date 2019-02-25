#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

// I wrote most of my data structure in a .h
// This is just for practice

int main() {
    struct table *t = createTable(5);
    insert(t, 2, 3);
    insert(t, 5, 4);
    printf("%d", lookup(t, 5));
    return 0;
}
