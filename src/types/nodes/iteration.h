#ifndef  IterationH
#define IterationH

#define iterate(manager, var) for (typeof(manager->start) var = manager->start; var != NULL; var = var->next) 

#define iterateWithIndex(manager, var, j) int j = 0; for (typeof(manager->start) var = manager->start; var != NULL; var = var->next, j++) 

#endif