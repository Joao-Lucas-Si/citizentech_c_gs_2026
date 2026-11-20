#include "./patient.h"
#include "../../types/nodes/iteration.h"
#include "../../types/nodes/manager.h"
#include "../../types/nodes/sorting.h"
#include "../../types/string.h"
#include "read_param.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DefineNodeManagerMethods(Patient);

NodeManager(Patient) * patients;

void initDatabase() {
  patients = createNodeManager(Patient);

  char linha[10000];
  FILE *file = fopen("assets/data.txt", "r");
  if (file != NULL) {
    while (fgets(linha, sizeof(linha), file)) {
      // printf("%s\n", linha);
      char **result = splitFirst(linha, ':');

      char *type = result[0];

      if (strcmp(type, "patient") == 0) {
        Patient test = readTest(result[1]);
        // printf("test: %s\n", test.name);
        addEnd(Patient)(patients, test);
      }
    }
  }
}

void saveDatabase() {
  FILE *file = fopen("assets/data.txt", "w");

  iterate(patients, i) {
    Patient value = i->value;
    fprintf(file, "patient:%s,%s,%d,%d,%d,%lld\n", value.name, value.condition,
            value.conditionPriority, value.position, value.id, value.date);
  }
  fclose(file);
}

NodeManager(Patient) * getPatients() { return patients; }

void addTest(Patient test) {
  addEnd(Patient)(patients, test);
  saveDatabase();
}

void updatePatient(int id, Patient newPatient) {
  Node(Patient) * saved;

  iterate(patients, i) {
    if (i->value.id == id) {
      saved = i;
      break;
    }
  }

  strcpy(saved->value.name, newPatient.name);
  strcpy(saved->value.condition, newPatient.condition);
  saved->value.conditionPriority = newPatient.conditionPriority;

  saveDatabase();
}

void removePatient(int id) {
  Patient toDelete;

  toDelete.id = id;

  removeEqual(Patient)(patients, toDelete, testEquals);
  updatePositions();
  saveDatabase();
}

Patient readTest(String message) {
  NodeManager(String) *param = splitParams(message);
  Patient test;

  test.name = param->array[0]->value;
  test.condition = param->array[1]->value;
  test.conditionPriority = atoi(param->array[2]->value);
  if (param->length > 3) {
    test.position = atoi(param->array[3]->value);
  }
  if (param->length > 4) {
    test.id = atoi(param->array[4]->value);
  }
  if (param->length > 5) {
    test.date = atoll(param->array[5]->value);
  }

  // test.quantity = atoi(param->array[3]->value);

  return test;
}

int testEquals(Patient test, Patient otherTest) {
  return test.id == otherTest.id;
}

void setPositions() {
  definePosition(0, getPatients());

  iterateWithIndex(getPatients(), i, j) { i->value.position = j + 1; }

  bubbleSort(orderId, 0, getPatients());
}

void updatePositions() {
  definePosition(0, getPatients());

  iterateWithIndex(getPatients(), i, j) { i->value.position = j + 1; }

  bubbleSort(orderId, 0, getPatients());
}