#include <stdio.h>

void sendResponse(char* content) {
    printf("%s\n", content);
    fflush(stdout);
}