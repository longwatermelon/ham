#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "node.h"


typedef struct
{
    Token* current_token;
    Token* prev_token;
    Lexer* lexer;
} Parser;

Parser* init_parser(const char* fp);
void parser_cleanup(Parser* parser);

void parser_eat(Parser* parser, int type);

Node* parser_parse(Parser* parser);
Node* parser_parse_expr(Parser* parser);

Node* parser_parse_string(Parser* parser);
Node* parser_parse_int(Parser* parser);
Node* parser_parse_id(Parser* parser);

Node* parser_parse_variable(Parser* parser);
Node* parser_parse_variable_definition(Parser* parser);
Node* parser_parse_function_call(Parser* parser);

#endif