#include "../include/node.h"
#include "../include/utils.h"


Node* init_node(int type)
{
    Node* node = malloc(sizeof(Node));

    node->type = type;

    // variable def
    node->variable_definition_name = (void*)0;
    node->variable_definition_value = (void*)0;

    // variable
    node->variable_name = (void*)0;

    // function call
    node->function_call_name = (void*)0;
    node->function_call_args = (void*)0;
    node->function_call_args_size = 0;

    // string
    node->string_value = (void*)0;

    // int
    node->int_value = 0;

    // compound
    node->compound_value = (void*)0;
    node->compound_size = 0;

    return node;
}


void node_cleanup(Node* node)
{
    safe_free(node->string_value);
    safe_free(node->function_call_name);
    safe_free(node->variable_definition_name);
    safe_free(node->variable_name);

    if (node->variable_definition_value)
    {
        node_cleanup(node->variable_definition_value);
    }

    if (node->function_call_args)
    {
        for (int i = 0; i < node->function_call_args_size; ++i)
        {
            node_cleanup(node->function_call_args[i]);
        }

        safe_free(node->function_call_args);
    }
    
    if (node->compound_value)
    {
        for (int i = 0; i < node->compound_size; ++i)
        {
            node_cleanup(node->compound_value[i]);
        }

        safe_free(node->compound_value);
    }

    safe_free(node);
}