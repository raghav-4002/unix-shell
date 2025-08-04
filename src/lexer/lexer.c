#include <stdlib.h>
#include <stdbool.h>

#include "lexer.h"
#include "token.h"


Token *tokens = NULL;
size_t cur_index = 0;

char *source = NULL;
size_t start = 0;
size_t current = 0;


bool
is_at_end()
{
    if (source[current] == '\n') return true;
    return false;
}


char
advance()
{
    current += 1;
    return source[current - 1];
}


void
add_token(Token_type type)
{

}


void
scan_token()
{
    char c = advance();

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
tokenize(char *input)
{
    source = input;

    while (!is_at_end()) {
        start = current;
        scan_token(source, &start, &current, &tokens, &cur_index);
    }

    // add last token of type `NIL`

    return tokens;
}
