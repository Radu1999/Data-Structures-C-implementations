#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#define MXLEN 1000


int main() {
    printf("Introdu sirul:\n");
    char *s = malloc(MXLEN * sizeof(char));
    struct Stack *stck  = malloc(sizeof(struct Stack));
    struct Node *rm;
    init_stack(stck);
    fgets(s, MXLEN, stdin);
    int n = strlen(s);
    for(int i = 0; i < n - 1; i++) {
        if(s[i] == '(' || s[i] == '[' || s[i] == '{') {
            if(s[i] == '[' && !is_empty_stack(stck) && *(char*)peek_stack(stck) == '(') {
                  printf("parantezare gresita");
                  free(s);
                  free(stck);
                  return 0;
            }
             if(s[i] == '{' && !is_empty_stack(stck) &&  (*(char*)peek_stack(stck) || '[' && *(char*)peek_stack(stck) == '(')) {
                  printf("parantezare gresita");
                  free(s);
                  free(stck);
                  return 0;
            }
            push_stack(stck, &s[i]);
        } else {
            if(*(char*)peek_stack(stck) + 1 == s[i] || *(char*)peek_stack(stck) + 2 == s[i]) {
                rm = pop_stack(stck);
                free(rm);
            } else {
                break;
            }
        }
    }
    if(is_empty_stack(stck)) {
        printf("parantezare corecta");
    } else {
        printf("parantezare gresita");
    }
    free(s);
    free(stck);

}
