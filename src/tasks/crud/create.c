#include "../../share/in/param.h"
#include "../../share/out.h"
#include "../../types/communs.h"
#include "../../types/string.h"
#include "../data/patient.h"
#include "../../types/nodes/sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void createPatient(Patient patient) {
  time_t now;
  time(&now);
  // struct tm *t = localtime(&now);
  // int minute = t->tm_min * 60;
  // long long int hours = t->tm_year * 24 * 60;
  // long long int  
  // long long int year 
  long long creationDate = (long long)now;
  patient.date = creationDate;
  patient.id = getPatients()->start != NULL ? getPatients()->end->value.id + 1 : 1;
  
  addTest(patient);

  updatePositions();
}

void createPatientMessage(String message) {
  // NodeManager(String) *param = splitParams(message);
  // Test test;

  // test.name = param->array[0]->value;
  // test.description = param->array[1]->value;
  // test.price = atof(param->array[2]->value);
  // test.quantity = atoi(param->array[3]->value);

  
  Patient patient = readTest(message);
  createPatient(patient);

  sendResponse(stringf(100, "nome: %s, condição: %s, prioridade:%d",
               patient.name, patient.condition, patient.conditionPriority));
  
}