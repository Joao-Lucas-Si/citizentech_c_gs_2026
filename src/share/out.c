#include <stdio.h>

void send(char* content) {
    printf("%s\n", content);
    fflush(stdout);
}