#include "../include/lexer.h"
#include "../include/utils.h"
#include <stdio.h>


int main(int argc, char** argv)
{
    Lexer* lexer = init_lexer("pront(\"Lawl\");");
    Token* t = init_token(TOKEN_ID, "");

    while ((t = lexer_get_next_token(lexer))->type != TOKEN_EOF)
    {
        printf("%d | %s\n", t->type, t->value);
        safe_free(t->value);
        safe_free(t);
    }

    return 0;
}