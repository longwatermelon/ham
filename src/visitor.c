#include "../include/visitor.h"
#include "../include/utils.h"
#include <stdio.h>
#include <string.h>


Visitor* init_visitor()
{
    Visitor* visitor = malloc(sizeof(Visitor));
    visitor->variable_defs = (void*)0;
    visitor->variable_defs_size = 0;

    return visitor;
}


Node* visitor_visit(Visitor* visitor, Node* node)
{
    if (!node) return node;

    switch (node->type)
    {
        case NODE_VARIABLE_DEFINITION: return visitor_visit_variable_definition(visitor, node);
        case NODE_VARIABLE: return visitor_visit_variable(visitor, node);
        case NODE_FUNCTION_CALL: return visitor_visit_function_call(visitor, node);
        case NODE_STRING: return node;
        case NODE_INT: return node;
        case NODE_COMPOUND: return visitor_visit_compound(visitor, node);
        case NODE_NOOP: return node;
    }

    printf("uncaught statemnet of type %d\n", node->type);
    exit(1);
}


Node* visitor_visit_variable_definition(Visitor* visitor, Node* node)
{
    ++visitor->variable_defs_size;

    if (!visitor->variable_defs)
    {
        visitor->variable_defs = malloc(sizeof(Node*));
        visitor->variable_defs[0] = node;
        ++visitor->variable_defs_size;
    }
    else
    {
        visitor->variable_defs = realloc(visitor->variable_defs, visitor->variable_defs_size * sizeof(Node));
        visitor->variable_defs[visitor->variable_defs_size - 1] = node;
    }

    return node;
}


Node* visitor_visit_variable(Visitor* visitor, Node* node)
{
    for (int i = 0; i < visitor->variable_defs_size; ++i)
    {
        Node* def = visitor->variable_defs[i];

        if (strcmp(def->variable_definition_name, node->variable_name) == 0)
        {
            return visitor_visit(visitor, def->variable_definition_value);
        }
    }

    printf("undefined variable '%s\n", node->variable_name);
}


Node* visitor_visit_compound(Visitor* visitor, Node* node)
{
    for (int i = 0; i < node->compound_size; ++i)
    {
        visitor_visit(visitor, node->compound_value[i]);
    }

    return (void*)0;
}


Node* visitor_visit_function_call(Visitor* visitor, Node* node)
{
    if (strcmp(node->function_call_name, "pront") == 0)
    {
        return builtin_function_print(visitor, node->function_call_args, node->function_call_args_size);
    }

    printf("undefined function '%s'\n", node->function_call_name);
    exit(1);
}


static void visitor_append_to_freed(Visitor* visitor, Node* node)
{
    ++visitor->nodes_to_free_size;

    if (!visitor->nodes_to_free)
    {
        visitor->nodes_to_free = malloc(sizeof(Node*));
        visitor->nodes_to_free[0] = node;
        ++visitor->nodes_to_free_size;
    }
    else
    {
        visitor->nodes_to_free = realloc(visitor->nodes_to_free, visitor->nodes_to_free_size * sizeof(Node));
        visitor->nodes_to_free[visitor->nodes_to_free_size - 1] = node;
    }
}


static Node* builtin_function_print(Visitor* visitor, Node** args, size_t args_size)
{
    for (size_t i = 0; i < args_size; ++i)
    {
        Node* visited = visitor_visit(visitor, args[i]);

        switch (visited->type)
        {
            case NODE_STRING: printf("%s ", visited->string_value); break;
            case NODE_INT: printf("%d ", visited->int_value); break;
            default: printf("%p ", visited);
        }
    }

    printf("\n");

    return (void*)0;
}