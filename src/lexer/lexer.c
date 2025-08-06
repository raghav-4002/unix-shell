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


/* ==================== Helper Functions ==================== */

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


bool
match(struct Parameters *parameters, char expected)
{
    char *source   = parameters->source;
    size_t current = parameters->current;

    if (source[current] == expected) {
        advance(parameters);  /* increment `current` by 1 */
        return true;
    }

    return false;
}


void
add_token(struct Parameters *parameters, Token_type type)
{
    Token *tokens    = parameters->tokens;
    size_t cur_index = parameters->cur_index;

    /* Resize array */
    tokens = realloc(tokens, (cur_index + 1) * sizeof(*tokens));

    /* Initialize with default values */
    tokens[cur_index].type          = type;
    tokens[cur_index].argv          = NULL;
    tokens[cur_index].argc          = 0;
    tokens[cur_index].return_status = UNDEFINED;

    if (!parameters->tokens) {
        parameters->tokens = tokens;
    }
    parameters->cur_index++;
}


void
scan_token(struct Parameters *parameters)
{
    char c = advance(parameters);

    switch (c) {
        /* Single character tokens */
        case ';': add_token(parameters, SEMICOLON); break;

        /* Double character tokens */
        case '|': 
            if (match(parameters, '|')) {
                add_token(parameters, LOGIC_OR);
            }
            else {
                add_token(parameters, PIPE);
            }
            break;

        case '&':
            if (match(parameters, '&')) {
                add_token(parameters, LOGIC_AND);
            }
            else {
                add_token(parameters, BG_OPERATOR);
            }
            break;
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

    /* Add `NIL` as last token */
    add_token(&parameters, NIL);

    return parameters.tokens;
}
