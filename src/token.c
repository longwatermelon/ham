#include "../include/token.h"
#include "../include/utils.h"
#include <stdlib.h>


Token* init_token(int type, char* value, bool is_trash)
{
    Token* t = malloc(sizeof(Token));
    t->type = type;
    t->value = value;
    t->is_trash = is_trash;

    return t;
}


void token_cleanup(Token* token)
{
    safe_free(token->value);
    safe_free(token);
}