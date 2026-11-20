#include "in.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void watch(void (*watcher)(char *message)) {
  char message[1000];
  while (fgets(message, sizeof(message), stdin)) {
    message[strlen(message) - 1] = 0;
    watcher(message);
  }
}
