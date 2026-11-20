#include "read_param.h"
#include "../../share/in/param.h"
#include "../../types/communs.h"
#include "../../types/nodes/manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DefineNodeManagerMethods(PatientCondition);

ReadParam parserReadParam(String message) {
  NodeManager(String) *params = splitParams(message);

  ReadParam param;

  param.order = params->start != NULL
                    ? strcmp(params->start->value, "position") == 0
                          ? orderPosition
                      : strcmp(params->start->value, "date") ? orderDate
                                                             : orderPriority
                    : orderId;
  // printf("%s", message);
  // printf("%s\n",params->array[1]->value);
  param.query = params->length > 1 ? params->start->next->value : "";

  // String splitedFilters = splitParams(char *message)
  NodeManager(PatientCondition) *filters = createNodeManager(PatientCondition);
  // if (params->length > 2) {

  //   NodeManager(String) *rawFilters =
  //       unpackNestedParam(params->array[2]->value);

  //   iterate(rawFilters, i) {
  //     addStart(PatientCondition)(filters, atoi(i->value));
  //   }
  // }
  param.filters = filters;
  // iterate(params, i) {
  //   free(i);
  // }
  // free(params);
  return param;
}