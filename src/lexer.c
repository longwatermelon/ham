#include "../include/lexer.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


Lexer* init_lexer(char* contents)
{
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->contents = contents;
    lexer->current_char = contents[0];
    lexer->index = 0;
    lexer->line_num = 1;
    
    return lexer;
}


void lexer_cleanup(Lexer* lexer)
{
    safe_free(lexer->contents);
    safe_free(lexer);
}


void lexer_advance(Lexer* lexer)
{
    if (lexer->current_char != '\0' && lexer->index < strlen(lexer->contents))
    {
        ++lexer->index;
        lexer->current_char = lexer->contents[lexer->index];
    }
}


char* lexer_collect_string(Lexer* lexer)
{
    lexer_advance(lexer);

    size_t start_index = lexer->index;

    while (lexer->current_char != '"' && lexer->current_char != '\n')
        lexer_advance(lexer);

    char* string = malloc((lexer->index - start_index) * sizeof(char) + 1);
    memcpy(string, &lexer->contents[start_index], lexer->index - start_index);
    string[(lexer->index - start_index) * sizeof(char)] = '\0';

    lexer_advance(lexer);

    return string;
}


char* lexer_collect_int(Lexer* lexer)
{
    size_t start_index = lexer->index;

    while (isdigit(lexer->current_char) && lexer->current_char != '\n')
        lexer_advance(lexer);

    char* integer = malloc((lexer->index - start_index) * sizeof(char) + 1);
    memcpy(integer, &lexer->contents[start_index], lexer->index - start_index);
    integer[(lexer->index - start_index) * sizeof(char)] = '\0';

    return integer;
}


char* lexer_collect_id(Lexer* lexer)
{
    size_t start_index = lexer->index;

    while (isalnum(lexer->current_char) && lexer->current_char != '\n')
        lexer_advance(lexer);

    char* id = malloc((lexer->index - start_index) * sizeof(char) + 1);
    memcpy(id, &lexer->contents[start_index], lexer->index - start_index);
    id[(lexer->index - start_index) * sizeof(char)] = '\0';

    return id;
}


char* lexer_collect_char_as_string(Lexer* lexer)
{
    char* string = malloc(2 * sizeof(char));
    string[0] = lexer->current_char;
    string[1] = '\0';

    return string;
}


Token* lexer_get_next_token(Lexer* lexer)
{
    while (lexer->index < strlen(lexer->contents))
    {
        while (iswspace(lexer->current_char) && lexer->current_char != '\n')
            lexer_advance(lexer);

        if (lexer->current_char == '"')
            return init_token(TOKEN_STRING, lexer_collect_string(lexer), false);
        
        if (isdigit(lexer->current_char))
            // is_trash set to true because the string value is casted and copied instead of directly copying the pointer, causing a memory leak
            return init_token(TOKEN_INT, lexer_collect_int(lexer), true);

        if (isalnum(lexer->current_char))
            return init_token(TOKEN_ID, lexer_collect_id(lexer), false);

        switch (lexer->current_char)
        {
            case ';': return lexer_awt(lexer, init_token(TOKEN_SEMI, lexer_collect_char_as_string(lexer), true));
            case '=': return lexer_awt(lexer, init_token(TOKEN_EQUALS, lexer_collect_char_as_string(lexer), true));
            case '(': return lexer_awt(lexer, init_token(TOKEN_LPAREN, lexer_collect_char_as_string(lexer), true));
            case ')': return lexer_awt(lexer, init_token(TOKEN_RPAREN, lexer_collect_char_as_string(lexer), true));
            case ',': return lexer_awt(lexer, init_token(TOKEN_COMMA, lexer_collect_char_as_string(lexer), true));
        }

        lexer_advance(lexer);
        ++lexer->line_num;
    }

    return init_token(TOKEN_EOF, calloc(1, sizeof(char)), true);
}


Token* lexer_awt(Lexer* lexer, Token* t)
{
    lexer_advance(lexer);
    return t;
}