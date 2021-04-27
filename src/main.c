#include "../include/lexer.h"
#include "../include/utils.h"
#include "../include/parser.h"
#include <stdio.h>


int main(int argc, char** argv)
{
    // Lexer* lexer = init_lexer("pront(\"Lawl\");");
    // Token* t = (void*)0;

    // while ((t = lexer_get_next_token(lexer))->type != TOKEN_EOF)
    // {
    //     printf("%d | %s\n", t->type, t->value);
    //     safe_free(t->value);
    //     safe_free(t);
    // }

    // safe_free(t->value);
    // safe_free(t);
    // safe_free(lexer);
    Parser* parser = init_parser(argv[1]);
    Node* root = parser_parse(parser);

    parser_cleanup(parser);
    node_cleanup(root);

    return 0;
}