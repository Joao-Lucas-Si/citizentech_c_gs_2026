#ifndef SortingH
#define SortingH
#include "manager.h"
#include "../../tasks/data/patient.h"
#include "../../tasks/data/read_param.h"

void bubbleSort(OrderType order, int inverse, NodeManager(Patient) * manager);

void definePosition(int inverse,
                    NodeManager(Patient) * manager);
#endif