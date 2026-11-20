#include "../../tasks/data/patient.h"
#include "../../tasks/data/read_param.h"
#include "iteration.h"
#include "manager.h"
#include "node.h"
#include <bits/types/cookie_io_functions_t.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int compareTestPrice(Node(Patient) * a1, Node(Patient) * a2) {
//   return a1->value.price > a2->value.price;
// }

// int compareTestQuantity(Node(Patient) * a1, Node(Patient) * a2) {
//   return a1->value.quantity > a2->value.quantity;
// }

int comparePatientPosition(Node(Patient) * a1, Node(Patient) * a2) {
  return a1->value.position > a2->value.position;
}

int comparePatientPriority(Node(Patient) * a1, Node(Patient) * a2) {
  return a1->value.conditionPriority < a2->value.conditionPriority;
}

int comparePatientDate(Node(Patient) * a1, Node(Patient) * a2) {
  return a1->value.date > a2->value.date;
}

int comparePatientId(Node(Patient) * a1, Node(Patient) * a2) {
  return a1->value.id > a2->value.id;
}

void bubbleSort(OrderType order, int inverse, NodeManager(Patient) * manager) {
  int trocado = 0;
  
  int (*compare)(Node(Patient) * i, Node(Patient) * next) =
      order == orderPosition   ? comparePatientPosition
      : order == orderDate     ? comparePatientDate
      : order == orderPriority ? comparePatientPriority

                               : comparePatientId;
  //   iterate(manager, var) { printf("t: %s\n", var->value.name); }
  do {
    trocado = 0;
    iterate(manager, i) {
      // printf("loop\n");
      //   printf("i: %s\n", i->value.name);
      if (i->next != NULL) {
        int compared = inverse ? compare(i->next, i) : compare(i, i->next);
        // printf("comparacao: %d, inverso: %d, id: %d, nextId: %d\n", compared,
        //        !compared, i->value.id, i->next->value.id);
        // compared = inverse ? !compared : compared;
        if (compared) {
          Node(Patient) *old = i->next;
          Node(Patient) *oldNext = old->next;
          old->next = i;
          old->previous = i->previous;
          i->next = oldNext;
          i->previous = old;
          trocado = 1;
          if (old->previous != NULL) {
            old->previous->next = old;
          }
          if (i->next != NULL) {
            i->next->previous = i;
          }
          if (old->previous == NULL) {
            manager->start = old;
          }
          if (i->next == NULL) {
            manager->end = i;
          }
        }
      }
    }
  } while (trocado);
}

void definePosition(int inverse, NodeManager(Patient) * manager) {
  int trocado = 0;

  //   iterate(manager, var) { printf("t: %s\n", var->value.name); }
  do {
    trocado = 0;
    iterate(manager, i) {
      //   printf("i: %s\n", i->value.name);
      if (i->next != NULL) {
        int compared =
            i->value.conditionPriority == i->next->value.conditionPriority
                ? i->value.date > i->next->value.date
                : i->value.conditionPriority > i->next->value.conditionPriority;
        if (inverse ? !compared : compared) {
          Node(Patient) *old = i->next;
          Node(Patient) *oldNext = old->next;
          old->next = i;
          old->previous = i->previous;
          i->next = oldNext;
          i->previous = old;
          trocado = 1;
          if (old->previous != NULL) {
            old->previous->next = old;
          }
          if (i->next != NULL) {
            i->next->previous = i;
          }
          if (old->previous == NULL) {
            manager->start = old;
          }
          if (i->next == NULL) {
            manager->end = i;
          }
        }
      }
    }
    // iterate(manager, i) {
    //   printf("%d - %lld, %d\n", i->value.position, i->value.date,
    //   i->value.conditionPriority);
    // }
    // if (trocado) {
    //   printf("trocado\n");
    // }else {
    //   printf("não trocado\n");
    // }
  } while (trocado);
}