#ifndef VISITOR_H
#define VISITOR_H
#include "node.h"
#include <stdlib.h>


typedef struct
{
    Node** variable_defs;
    size_t variable_defs_size;
} Visitor;


Visitor* init_visitor();
void visitor_cleanup(Visitor* visitor);

Node* visitor_visit(Visitor* visitor, Node* node);

Node* visitor_visit_variable_definition(Visitor* visitor, Node* node);
Node* visitor_visit_variable(Visitor* visitor, Node* node);

Node* visitor_visit_compound(Visitor* visitor, Node* node);

Node* visitor_visit_function_call(Visitor* visitor, Node* node);

static Node* builtin_function_print(Visitor* visitor, Node** args, size_t args_size);

#endif