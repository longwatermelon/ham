#include "../include/lexer.h"
#include "../include/utils.h"
#include "../include/parser.h"
#include "../include/visitor.h"
#include <stdio.h>


int main(int argc, char** argv)
{
    Parser* parser = init_parser(argv[1]);
    Node* root = parser_parse(parser);

    Visitor* visitor = init_visitor();
    visitor_visit(visitor, root);

    parser_cleanup(parser);
    node_cleanup(root);
    safe_free(visitor);

    return 0;
}