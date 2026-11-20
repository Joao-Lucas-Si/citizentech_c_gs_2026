#include "../../types/communs.h"
#include "../../types/nodes/manager.h"
#include "../../types/string.h"
#include "../out.h"
#include <stdio.h>
#include <string.h>

NodeManager(String) * splitParams(char *message) {
  NodeManager(String) *manager = createNodeManager(String);

  char *content = message;
  while (1) {
    char **splited = splitFirstNested(content, ',');
    // printf("0: %ld, %s\n", strlen(splited[0]), splited[0]);
    // printf("1: %ld, %s\n", strlen(splited[1]), splited[1]);
    // debug(stringf(100, "0: %ld, %s\n", strlen(splited[0]), splited[0]));
    // if (strlen(splited[0]) > 0) {
    addEnd(String)(manager, splited[0]);
    // }
    if (strlen(splited[1]) == 0) {
      break;
    } else {
      content = splited[1];
    }
  }

  return manager;
}

NodeManager(String) * unpackNestedParam(char *nested) {
  // String filterMessage = params->array[2]->value;

  memmove(nested, nested + 1, strlen(nested));

  nested[strlen(nested) - 1] = 0;

  NodeManager(String) *nestedParams = splitParams(nested);

  return nestedParams;
}
