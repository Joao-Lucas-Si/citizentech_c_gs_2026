#ifndef CreatorH
#define CreatorH
#include "iteration.h"
#include "node.h"
#include <stdio.h>

#define NodeManager(type) node_manager_##type

// #define createNodeManager(type) createNodeManager##type

#define createNodeManager(type)                                                \
  ({                                                                           \
    NodeManager(type) *instance = malloc(sizeof(NodeManager(type)));           \
    instance->length = 0;                                                      \
    instance->start = NULL;                                                    \
    instance->end = NULL;                                                      \
    instance->array = malloc(0);                                               \
    instance;                                                                  \
  })

#define DefineAddStartType(type)                                               \
  void addStartNode##type(NodeManager(type) * manager, type value);

#define DefineRemoveEqualType(type)                                            \
  void removeEqual##type(NodeManager(type) * manager, type target,             \
                         int (*equals)(type self, type other))

#define DefineRemoveEqual(type)                                                \
  void removeEqual##type(NodeManager(type) * manager, type target,             \
                         int (*equals)(type self, type other)) {               \
    int count = 0;                                                             \
    iterate(manager, i) {                                                      \
      if (equals(target, i->value)) {                                          \
        Node(type) *next = i->next;                                            \
        Node(type) *previous = i->previous;                                    \
        if (next != NULL) {                                                    \
          next->previous = previous;                                           \
        }                                                                      \
        if (previous != NULL) {                                                \
          previous->next = next;                                               \
        }                                                                      \
        free(i);                                                               \
        if (count == 0) {                                                      \
          manager->start = next;                                               \
        }                                                                      \
        if (count == manager->length + 1) {                                    \
          manager->end = previous;                                             \
        }                                                                      \
        manager->length--;                                                     \
        break;                                                                 \
      }                                                                        \
      count++;                                                                 \
    }                                                                          \
  }

#define removeEqual(type) removeEqual##type

#define DefineAddEnd(type)                                                     \
  void addEndNode##type(NodeManager(type) * manager, type value) {             \
    Node(type) *newNode = createNode(type)(value);                             \
    if (manager->start == NULL) {                                              \
      manager->start = newNode;                                                \
      manager->end = newNode;                                                  \
    } else {                                                                   \
      Node(type) *old = manager->end;                                          \
      old->next = newNode;                                                     \
      newNode->previous = old;                                                 \
      manager->end = newNode;                                                  \
    }                                                                          \
    manager->length += 1;                                                      \
    manager->array =                                                           \
        realloc(manager->array, manager->length * sizeof(Node(type)));         \
    manager->array[manager->length - 1] = newNode;                             \
  }

#define DefineAddEndType(type)                                                 \
  void addEndNode##type(NodeManager(type) * manager, type value);

#define addEnd(type) addEndNode##type

#define DefineAddStart(type)                                                   \
  void addStartNode##type(NodeManager(type) * manager, type value) {           \
    Node(type) *newNode = createNode(type)(value);                             \
    if (manager->start == NULL) {                                              \
      manager->start = newNode;                                                \
      manager->end = newNode;                                                  \
    } else {                                                                   \
      Node(type) *old = manager->start;                                        \
      old->previous = newNode;                                                 \
      newNode->next = old;                                                     \
      manager->start = newNode;                                                \
    }                                                                          \
    manager->length += 1;                                                      \
    manager->array =                                                           \
        realloc(manager->array, manager->length * sizeof(Node(type)));         \
    manager->array[manager->length - 1] = newNode;                             \
  }

#define addStart(type) addStartNode##type

#define DefineNodeManager(type)                                                \
  DefineNodeManagerType(type);                                                 \
  DefineNodeManagerMethods(type)

#define DefineNodeManagerType(type)                                            \
  CreateNodeType(type);                                                        \
  typedef struct struc_node_manager_##type {                                   \
    int length;                                                                \
    Node(type) * *array;                                                       \
    Node(type) * start;                                                        \
    Node(type) * end;                                                          \
  } NodeManager(type);                                                         \
  DefineAddStartType(type);                                                    \
  DefineAddEndType(type);                                                      \
  DefineRemoveEqualType(type)

#define DefineNodeManagerMethods(type)                                         \
  DefineAddStart(type);                                                        \
  DefineNodeMethods(type);                                                     \
  DefineAddEnd(type);                                                          \
  DefineRemoveEqual(type);

#endif