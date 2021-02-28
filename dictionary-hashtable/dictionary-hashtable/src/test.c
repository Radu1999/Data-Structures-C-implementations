#include <stdio.h>
#include <stdlib.h>

void print(void *c) {
    printf("%c", *((char *)c + 1));
}

int main () {
    char* s = malloc(100 * sizeof(char));
    fgets(s, 100, stdin);
    print(&s[2]);
}