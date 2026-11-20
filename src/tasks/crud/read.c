#include "../../share/out.h"
#include "../../types/communs.h"
#include "../../types/nodes/iteration.h"
#include "../../types/nodes/sorting.h"
#include "../../types/string.h"
#include "../data/patient.h"
#include "../data/read_param.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NodeManager(Patient)* readPatients(ReadParam param) {
  NodeManager(Patient) *results = createNodeManager(Patient);
  iterate(getPatients(), i) {

    if (param.filters->length > 0) {
      int valid = 1;

      iterate(param.filters, j) {
        if (i->value.conditionPriority == j->value) {

          valid = 1;
          break;
        }
      }
      if (!valid) {
        continue;
      }
    }
    if (strstr(i->value.name, param.query) != NULL ||
        strstr(i->value.condition, param.query) != NULL) {
      addStart(Patient)(results, i->value);
    }
  }
  bubbleSort(param.order, 0, results);
  return results;
}

void read(String message) {
  send("start:product");
  ReadParam param = parserReadParam(message);
  // printf("query: %s\n", param.query);
  NodeManager(Patient)* results = readPatients(param);
  
  iterate(results, i) {
    Patient value = i->value;
    String parsed = stringf(1000, "%s,%s,%d,%d,%d,%d", value.name,
                            value.condition, value.conditionPriority,
                            value.position, value.id, value.date);
    send(parsed);
  }
  send("end");
  // iterate(results, i) {
  //   free(i);
  // }
  free(results);
}