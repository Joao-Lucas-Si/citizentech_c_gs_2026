#include "../../share/in/param.h"
#include "../../share/out.h"
#include "../../types/communs.h"
#include "../../types/nodes/sorting.h"
#include "../../types/string.h"
#include "../data/patient.h"
#include <stdio.h>
#include <stdlib.h>

void updatePatientAction(int id, Patient patient) {
  updatePatient(id, patient);

  updatePositions();

  saveDatabase();

}

void update(String message) {

  char **spplited = splitFirst(message, ',');

  int id = atoi(spplited[0]);

  Patient patient = readTest(spplited[1]);

  updatePatientAction(id, patient);
  sendResponse(stringf(100, "nome: %s, condição: %s, prioridade:%d", patient.name,
               patient.condition, patient.conditionPriority));
}