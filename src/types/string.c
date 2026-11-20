#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *stringf(int length, char *restrict format, ...) {
  va_list args;
  va_start(args, format);
  char *string = malloc(length);
  vsprintf(string, format, args);
  va_end(args);

  return string;
}

char **splitFirst(char *original, char character) {
  char **result = malloc(2 * sizeof(char *));
  result[0] = malloc(strlen(original));
  result[1] = malloc(strlen(original));
  int headSize = 0;
  int tailSize = 0;
  int size = strlen(original);
  int found = 0;
  for (int i = 0; i < size; i++) {
    if (!found && original[i] == character) {
      found = 1;
    } else if (found) {
      result[1][tailSize] = original[i];
      tailSize++;
    } else {
      result[0][headSize] = original[i];
      headSize++;
    }
  }

  result[1][tailSize] = 0;
  result[0][headSize] = 0;

  return result;
}

char **splitFirstNested(char *original, char character) {
  char **result = malloc(2 * sizeof(char *));
  result[0] = malloc(strlen(original));
  result[1] = malloc(strlen(original));
  int headSize = 0;
  int tailSize = 0;
  int size = strlen(original);
  int found = 0;
  int isNested = original[0] == '(';
  int openCount = 0;
  int closeCount = 0;
  for (int i = 0; i < size; i++) {
    if (original[i] == '(') {
      openCount++;
    }
    else if (original[i] == ')') {
      closeCount++;
    }
    if (!found && original[i] == character &&
        ((isNested && original[i - 1] == ')' && openCount == closeCount) ||
         !isNested)) {
      found = 1;
    } else if (found) {
      result[1][tailSize] = original[i];
      tailSize++;
    } else {
      result[0][headSize] = original[i];
      headSize++;
    }
  }

  result[1][tailSize] = 0;
  result[0][headSize] = 0;

  return result;
}

int startWith(char *original, char *content) {
  return strncmp(original, content, strlen(content)) == 0;
}