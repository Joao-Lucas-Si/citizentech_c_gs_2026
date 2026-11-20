#include "engine.h"
#include "../../types/nodes/iteration.h"
#include "../../types/nodes/manager.h"
#include "../../types/string.h"
#include "../in.h"
#include "../out.h"
#include <stdlib.h>
#include <string.h>

typedef Listener *ListenerPointer;

DefineNodeManager(ListenerPointer)

NodeManager(ListenerPointer) *listeners = NULL;

void engineWatcher(char *message) {
  Listener *target = NULL;
  char **splitedMessage = splitFirst(message, ':');
  char *type = splitedMessage[0];
  iterate(listeners, i) {
    if (strcmp(type, i->value->preffix) == 0) {
      target = i->value;
      break;
    }
  }

  if (target != NULL) {
    target->handler(splitedMessage[1]);
  } else {
    send(stringf(1000, "ERROR: unknow message: %s", type));
  }
}

void initEngine() {
  if (listeners == NULL) {
    listeners = createNodeManager(ListenerPointer);
  }
}

void engine() { watch(engineWatcher); }

void registerInput(char *preffix, Handler handler) {

  Listener *new = malloc(sizeof(Listener));
  new->preffix = preffix;
  new->handler = handler;
  addStart(ListenerPointer)(listeners, new);
}