#ifndef TOKEN_H
#define TOKEN_H


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
} Token;

Token* init_token(int type, char* value);
void token_cleanup(Token* token);

#endif