#ifndef NODE_H
#define NODE_H
#include <stdlib.h>


typedef struct NODE_STRUCT
{
    enum
    {
        NODE_VARIABLE_DEFINITION,
        NODE_VARIABLE,
        NODE_FUNCTION_CALL,
        NODE_INT,
        NODE_STRING,
        NODE_COMPOUND,
        NODE_NOOP
    } type;

    // variable def
    char* variable_definition_name;
    struct NODE_STRUCT* variable_definition_value;

    // variable
    char* variable_name;

    // function call
    char* function_call_name;
    struct NODE_STRUCT** function_call_args;
    size_t function_call_args_size;

    // string
    char* string_value;

    // int
    int int_value;

    // compound
    struct NODE_STRUCT** compound_value;
    size_t compound_size;

} Node;

Node* init_node(int type);
void node_cleanup(Node* node);

#endif