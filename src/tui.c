#include "./tasks/crud/read.h"
#include "./tasks/data/patient.h"
#include "./tasks/data/read_param.h"
#include "./types/nodes/manager.h"
#include "tasks/crud/create.h"
#include "tasks/crud/update.h"
#include "types/nodes/iteration.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN32)
#define eWindows 1
#else
#define eWindows 0
#endif

#if eWindows
#include <windows.h>
#endif

void limpar() {
  if (eWindows) {
    system("cls");
  } else {
    printf("\033c");
  }
}

void searchPage(ReadParam *param) {
  char query[100];
  printf("escrava sua consulta: ");
  // scanf("\n");
  int c = 0;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
  // scanf("%[^\n]s", query);
  fgets(query, 100, stdin);
  query[strcspn(query, "\n")] = 0;
  strcpy(param->query, query);
}

void orderPage(ReadParam *param) {
  while (1) {
    printf("escolha qual ordem: \n");
    printf("0 - sair\n");
    printf("1 - prioridade\n");
    printf("2 - posição\n");
    printf("3 - data\n");
    printf("4 - id\n");
    printf("escolha: ");
    int opcao;
    scanf("%d", &opcao);
    limpar();
    if (opcao == 0) {
      break;
    }

    if (opcao > 0 && opcao < 5) {
      opcao--;
      param->order = opcao;
      break;
    }
    printf("opção invalida\n");
  }
}

void visualizar() {
  char query[100] = "";
  NodeManager(PatientCondition) *filters = createNodeManager(PatientCondition);

  ReadParam params = {
      .query = query, .filters = filters, .order = orderPosition
      // .filters=
  };
  while (1) {

    NodeManager(Patient) *patients = readPatients(params);
    iterateWithIndex(patients, patient, i) {
      printf("--------------\n");
      printf("%d - %s\n", i, patient->value.name);
      printf("id: %d\n", patient->value.id);
      printf("posição: %d\n", patient->value.position);
      printf("condição: %s\n", patient->value.condition);
      PatientCondition priority = patient->value.conditionPriority;
      printf("prioridade: %s\n",
             priority == UrgentCondition
                 ? "urgente"
                 : (priority == IntermediateCondition ? "intermediario"
                                                      : "simples"));
    }
    if (patients->length == 0) {
      printf("nenhum paciente cadastrado\n");
    }
    printf("--------------\n");
    printf("opções:\n");
    printf("0 - voltar\n");
    printf("1 - ordenar\n");
    printf("2 - pesquisar\n");
    int opcao;
    scanf("%d", &opcao);
    limpar();
    iterate(patients, patient) { free(patient); }
    free(patients);
    if (opcao < 0 || opcao > 3) {

      printf("opção invalida\n");
    }
    if (opcao == 0) {
      break;
    }
    if (opcao == 1) {
      orderPage(&params);
    }
    if (opcao == 2) {
      searchPage(&params);
    }
  }
}

Patient form() {
  char *name = malloc(100);
  char *condition = malloc(500);
  Patient data = {
      .name = name,
      .condition = condition,
  };
  printf("nome: ");
  scanf("%s", name);
  printf("condição: ");
  scanf("%s", condition);
  int prioridade;
  while (1) {
    printf("prioridade(0 - urgente, 1 - intermediario, 2 - simples): ");
    scanf("%d", &prioridade);
    if (prioridade >= 0 && prioridade <= 2) {
      break;
    }
    printf("prioridade invalida\n");
  }
  data.conditionPriority = prioridade;
  return data;
}

void create() {
  Patient patient = form();

  createPatient(patient);
}

void deletar() {
  NodeManager(Patient) *patients = getPatients();

  while (1) {

    printf("digite o id de quem você deseja editar:\n");
    iterateWithIndex(patients, i, j) {
      printf("%d - %s\n", i->value.id, i->value.name);
    }
    printf("ou digite 0 para voltar\n");
    int opcao;
    printf("escolha: ");
    scanf("%d", &opcao);
    limpar();
    if (opcao == 0) {
      break;
    }
    removePatient(opcao);
  }
}

void atualizar() {
  NodeManager(Patient) *patients = getPatients();

  while (1) {

    printf("digite o id de quem você deseja editar:\n");
    iterateWithIndex(patients, i, j) {
      printf("%d - %s\n", i->value.id, i->value.name);
    }
    printf("ou digite 0 para voltar\n");
    int opcao;
    printf("escolha: ");
    scanf("%d", &opcao);
    limpar();
    if (opcao == 0) {
      break;
    }

    Patient data = form();
    int salvo = updatePatientAction(opcao, data);
    if (salvo) {
      break;
    }
    limpar();
    printf("id incorreto\n");
  }
}

void menu() {
  int continuar = 1;
  while (continuar) {
    printf("escolha uma opção\n");
    printf("0 - sair\n");
    printf("1 - visualizar\n");
    printf("2 - criar\n");
    printf("3 - atualizar\n");
    printf("4 - deletar\n");
    int opcao;
    printf("escolha: ");
    scanf("%d", &opcao);

    limpar();
    if (opcao < 0 || opcao > 5) {
      printf("opção invalida\n");
      continue;
    }
    switch (opcao) {
    case 0:
      continuar = 0;
      break;
    case 1:
      visualizar();
      break;
    case 2:
      create();
      break;
    case 3:
      atualizar();
      break;
    case 4:
      deletar();
      break;
    }
  }
}

void createTui() { menu(); }