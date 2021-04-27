#ifndef TOKEN_H
#define TOKEN_H
#include <stdbool.h>


typedef struct
{
    enum
    {
        TOKEN_ID,
        TOKEN_SEMI,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_EQUALS,
        TOKEN_STRING,
        TOKEN_INT,
        TOKEN_COMMA,
        TOKEN_EOF
    } type;

    char* value;
    bool is_trash;
} Token;

Token* init_token(int type, char* value, bool is_trash);
void token_cleanup(Token* token);

#endif