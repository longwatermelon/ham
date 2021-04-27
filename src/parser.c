#include "../include/parser.h"
#include "../include/utils.h"
#include <string.h>
#include <stdio.h>


Parser* init_parser(const char* fp)
{
    Parser* parser = malloc(sizeof(Parser));
    char* contents = read_file(fp);
    parser->lexer = init_lexer(contents);
    parser->current_token = lexer_get_next_token(parser->lexer);
    parser->prev_token = malloc(sizeof(Token));

    return parser;
}


void parser_cleanup(Parser* parser)
{
    token_cleanup(parser->current_token);
    token_cleanup(parser->prev_token);

    lexer_cleanup(parser->lexer);
    free(parser);
}


void parser_eat(Parser* parser, int type)
{
    if (parser->current_token->type == type)
    {
        parser->prev_token->type = parser->current_token->type;
        parser->prev_token->value = parser->current_token->value;

        safe_free(parser->current_token);
        parser->current_token = lexer_get_next_token(parser->lexer);
    }
    else
    {
        printf("unexpected token '%s' at line %d\n", parser->current_token->value, parser->lexer->line_num);
        exit(1);
    }
}


Node* parser_parse(Parser* parser)
{
    Node* root = init_node(NODE_COMPOUND);

    root->compound_value = malloc(sizeof(Node*));
    root->compound_value[0] = parser_parse_expr(parser);
    ++root->compound_size;

    while (parser->lexer->index < strlen(parser->lexer->contents))
    {
        parser_eat(parser, TOKEN_SEMI);

        Node* expr = parser_parse_expr(parser);

        if (!expr) break;

        ++root->compound_size;
        root->compound_value = realloc(root->compound_value, sizeof(Node*) * root->compound_size);
        root->compound_value[root->compound_size - 1] = expr;
    }

    return root;
}


Node* parser_parse_expr(Parser* parser)
{
    switch (parser->current_token->type)
    {
        case TOKEN_STRING: return parser_parse_string(parser);
        case TOKEN_INT: return parser_parse_int(parser);
        case TOKEN_ID: return parser_parse_id(parser);
    }

    return (void*)0;
}


Node* parser_parse_string(Parser* parser)
{
    Node* node_str = init_node(NODE_STRING);
    node_str->string_value = parser->current_token->value;

    parser_eat(parser, TOKEN_STRING);

    return node_str;
}


Node* parser_parse_int(Parser* parser)
{
    Node* node_int = init_node(NODE_INT);
    node_int->int_value = atoi(parser->current_token->value);

    parser_eat(parser, TOKEN_INT);

    return node_int;
}


Node* parser_parse_id(Parser* parser)
{
    if (strcmp(parser->current_token->value, "def") == 0)
    {
        return parser_parse_variable_definition(parser);
    }
    else
    {
        return parser_parse_variable(parser);
    }
}


Node* parser_parse_variable(Parser* parser)
{
    char* token_value = parser->current_token->value;
    parser_eat(parser, TOKEN_ID);

    if (parser->current_token->type == TOKEN_LPAREN)
    {
        return parser_parse_function_call(parser);
    }

    Node* node_var = init_node(NODE_VARIABLE);
    node_var->variable_name = token_value;

    return node_var;
}


Node* parser_parse_variable_definition(Parser* parser)
{
    parser_eat(parser, TOKEN_ID);

    char* name = parser->current_token->value;

    parser_eat(parser, TOKEN_ID);
    parser_eat(parser, TOKEN_EQUALS);

    Node* value = parser_parse_expr(parser);

    Node* variable_def = init_node(NODE_VARIABLE_DEFINITION);

    variable_def->variable_name = name;

    variable_def->variable_definition_value = value;

    return variable_def;
}


Node* parser_parse_function_call(Parser* parser)
{
    Node* function_call = init_node(NODE_FUNCTION_CALL);

    function_call->function_call_name = parser->prev_token->value;

    parser_eat(parser, TOKEN_LPAREN);

    function_call->function_call_args = malloc(sizeof(Node*));

    function_call->function_call_args[0] = parser_parse_expr(parser);
    ++function_call->function_call_args_size;

    while (parser->current_token->type != TOKEN_RPAREN)
    {
        parser_eat(parser, TOKEN_COMMA);

        Node* expr = parser_parse_expr(parser);

        ++function_call->function_call_args_size;
        function_call->function_call_args = realloc(
            function_call->function_call_args,
            function_call->function_call_args_size * sizeof(Node*)
        );

        function_call->function_call_args[function_call->function_call_args_size - 1] = expr;
    }

    parser_eat(parser, TOKEN_RPAREN);

    return function_call;
}