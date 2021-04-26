#include "../include/token.h"
#include "../include/utils.h"
#include <stdlib.h>


Token* init_token(int type, char* value)
{
    Token* t = malloc(sizeof(Token));
    t->type = type;
    t->value = value;

    return t;
}