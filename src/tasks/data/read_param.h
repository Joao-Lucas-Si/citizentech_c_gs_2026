#ifndef ReadParamH
#define ReadParamH
#include "../../types/communs.h"
#include "patient.h"
#include "../../types/nodes/manager.h"

typedef enum { orderPriority, orderPosition, orderDate, orderId } OrderType;

DefineNodeManagerType(PatientCondition);

typedef struct {
  OrderType order;
  String query;
  NodeManager(PatientCondition)* filters;
} ReadParam;

ReadParam parserReadParam(String message);

#endif