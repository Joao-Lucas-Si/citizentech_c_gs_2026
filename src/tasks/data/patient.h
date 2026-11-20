#ifndef TestH
#define TestH
#include "../../share/in/param.h"
#include "../../types/communs.h"
#include "../../types/nodes/manager.h"

typedef enum {
  UrgentCondition,
  IntermediateCondition,
  SimpleCondition,
} PatientCondition;

// enum Type {

// };

void saveDatabase() ;

typedef struct {
  int id;
  String name;
  String condition;
  PatientCondition conditionPriority;
  int position;
  long long date;
} Patient;

DefineNodeManagerType(Patient);

void initDatabase();

NodeManager(Patient) * getPatients();

Patient readTest(String message);

void addTest(Patient test);

void removePatient(int id);

int testEquals(Patient test, Patient otherTest);

int updatePatient(int id, Patient newData);
void updatePositions() ;
#endif