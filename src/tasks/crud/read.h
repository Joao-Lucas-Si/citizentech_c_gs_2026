#ifndef ReadH
#define ReadH
#include "../../types/nodes/manager.h"
#include "../data/patient.h"
#include "../data/read_param.h"

NodeManager(Patient)* readPatients(ReadParam param);
#endif