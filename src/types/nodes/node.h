#ifndef NodeH
#define NodeH

#define Node(type) node_##type

#define DefineGetChainEnd(type) Node(type)* getChainEnd##type(Node(type)* start) {\
    \
}

#define createNode(type) createNode##type

#define DefineCreateNodeType(type) Node(type)* createNode##type(type value);

#define DefineCreateNode(type) Node(type)* createNode##type(type value) {\
    Node(type)* node = malloc(sizeof(Node(type)));\
    node->value = value;\
    node->next = NULL;\
    node->previous = NULL;\
    return node;\
}

#define CreateNode(type) CreateNodeType(type);\
DefineNodeMethods(type)

#define CreateNodeType(type) typedef struct struc_node_##type {\
    type value;\
    struct struc_node_##type* next;\
    struct struc_node_##type* previous;\
} Node(type);\
DefineCreateNodeType(type)


#define DefineNodeMethods(type) DefineCreateNode(type)

#endif