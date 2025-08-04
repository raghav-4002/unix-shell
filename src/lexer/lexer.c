#include <stdlib.h>
#include <stdbool.h>

#include "lexer.h"
#include "token.h"


struct Parameters
{
    Token *tokens;
    size_t cur_index;

    char *source;
    size_t start;
    size_t current;
};


void
init_parameters(struct Parameters *parameters, char *input)
{
    parameters->tokens    = NULL;
    parameters->cur_index = 0;

    parameters->source    = input;
    parameters->start     = 0;
    parameters->current   = 0;
}


bool
is_at_end(struct Parameters *parameters)
{
    char *source   = parameters->source;
    size_t current = parameters->current;

    if (source[current] == '\n') return true;

    return false;
}


char
advance(struct Parameters *parameters)
{
    parameters->current += 1;

    size_t current = parameters->current;
    char *source   = parameters->source;

    return source[current - 1];
}


void
add_token(Token_type type)
{

}


void
scan_token(struct Parameters *parameters)
{
    char c = advance(parameters);

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
    struct Parameters parameters;
    init_parameters(&parameters, input);

    while (!is_at_end(&parameters)) {
        parameters.start = parameters.current;
        scan_token(&parameters);
    }

    // add last token of type `NIL`

    return parameters.tokens;
}
