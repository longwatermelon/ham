#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <stdlib.h>


typedef struct
{
    char current_char;
    size_t index;
    char* contents;
    size_t line_num;
} Lexer;

Lexer* init_lexer(char* contents);
void lexer_cleanup(Lexer* lexer);

void lexer_advance(Lexer* lexer);

char* lexer_collect_string(Lexer* lexer);
char* lexer_collect_int(Lexer* lexer);
char* lexer_collect_id(Lexer* lexer);

char* lexer_collect_char_as_string(Lexer* lexer);

Token* lexer_get_next_token(Lexer* lexer);

Token* lexer_awt(Lexer* lexer, Token* t);

#endif