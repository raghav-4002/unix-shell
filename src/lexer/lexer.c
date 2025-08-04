#include <stdlib.h>
#include <stdbool.h>

#include "lexer.h"
#include "token.h"



bool
is_at_end(char *source, size_t current)
{
    if (source[current] == '\n') return true;

    return false;
}


char
advance(char *source, size_t *current)
{
    *current += 1;

    return source[(*current) - 1];
}


void
add_token(char *source, size_t *start, size_t *current,
          Token **tokens, size_t *cur_index)
{

}


void
scan_token(char *source, size_t *start, size_t *current, 
           Token **tokens, size_t *cur_index)
{
    char c = advance(source, current);

    switch (c) {
        case ';': add_token(SEMICOLON); break;
    }
}


/*
 * @brief : Tokenizes an input string; stops when encounters `\0`
 * @param : An input string
 * @return: An array of type `Token`; last element is type `NIL`
 */
Token *
tokenize(char *source)
{
    Token *tokens = NULL;
    size_t cur_index = 0;

    size_t start = 0;
    size_t current = 0;

    while (!is_at_end(source, current)) {
        start = current;
        scan_token(source, &start, &current, &tokens, &cur_index);
    }

    // add last token of type `NIL`

    return tokens;
}
