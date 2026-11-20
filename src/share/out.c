#include "out.h"
#include <stdio.h>

void sendResponse(char* content) {
    printf("%s\n", content);
    fflush(stdout);
}

void debug(char *content) {
    printf("debug: %s\n", content);
}