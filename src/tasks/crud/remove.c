#include "../../types/communs.h"
#include "../data/patient.h"
#include "../../share/out.h"


void delete(String message) {
    removePatient(atoi(message));
    sendResponse("deleted");
}