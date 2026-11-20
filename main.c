#include "src/share/in.c"
#include "src/share/in/engine.c"
#include "src/share/in/param.c"
#include "src/share/in/param.h"
#include "src/share/out.c"
#include "src/share/out.h"
#include "src/tasks/crud/create.c"
#include "src/tasks/crud/read.c"
#include "src/tasks/crud/remove.c"
#include "src/tasks/crud/update.c"
#include "src/tasks/data/patient.c"
#include "src/tasks/data/patient.h"
#include "src/tasks/data/read_param.c"
#include "src/types/communs.h"
#include "src/types/nodes/iteration.h"
#include "src/types/nodes/manager.h"
#include "src/types/nodes/node.h"
#include "src/types/nodes/sorting.c"
#include "src/tui.c"
#include "src/types/string.c"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DefineNodeManagerMethods(int);

DefineNodeManagerMethods(String);

void listen(char *message) {

  //   send(stringf(200, "%s%s", message, message));
}

void receiver(char *message) {
  NodeManager(String) *params = splitParams(message);
  // printf("%s", message);
  // send( stringf(100, "%d", params->length));
  iterate(params, i) { send(stringf(90, "%s -> ", i->value)); }
  //   send(stringf(100, "received: %s", message)); }
}

void createEngine() {
  initEngine();
 
  registerInput("receive", receiver);
  registerInput("create", createPatientMessage);
  registerInput("read", read);
  registerInput("delete", delete);
  registerInput("update", update);
  engine();
}

int main(int argc, char* argsv[]) {
   initDatabase();
  if (argc == 2 && strcmp(argsv[1], "--engine") == 0 ) {
    createEngine();
  }else {
    createTui();
  }
  /*NodeManager(int) *manager = createNodeManager(int);
  // int a = manager.end->previous->value;
  // printf("%p", manager->start);
  addStart(int)(manager, 2);
  addStart(int)(manager, 10);
  addStart(int)(manager, 28);
  addStart(int)(manager, 69);
  // printf("%p", manager->start);
  iterate(int, manager, var) { printf("%d -> ", var->value); }

  printf("null \n");
  for (int i = 0; i < manager->length; i++) {
    printf("%d <- ", manager->array[i]->value);
  }

  printf("null \n");*/

  // watch(listen);
  /*char linha[1000];
  while (fgets(linha, sizeof(linha), stdin)) {

  }*/
}