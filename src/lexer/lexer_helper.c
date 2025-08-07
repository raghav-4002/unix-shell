#include <string.h>

#include "lexer_helper.h"


void
init_parameters(struct Parameters *parameters, char *input)
{
    parameters->tokens    = NULL;
    parameters->arr_size  = 0;

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
init_token(Token *token, Token_type type)
{
    token->type          = type;
    token->arg           = NULL;
    token->return_status = UNDEFINED;
}


char *
create_substring(char *string, size_t start, size_t end)
{
    size_t buf_size = (end - start) + 1; /* `+1` for null-byte */

    /* Dynamicllay allocating as contents should persist */
    char *substring = malloc(buf_size * sizeof(*substring));

    /* Update string to be the new substring */
    string = &string[start];
    string[end] = '\0';

    strncpy(substring, string, buf_size);

    return substring;
}
