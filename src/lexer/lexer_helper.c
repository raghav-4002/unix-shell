#include <stdlib.h>
#include <string.h>

#include "lexer_helper.h"
#include "../utils.h"


void
init_parameters(struct Parameters *parameters, char *input)
{
    parameters->tokens    = NULL;
    parameters->arr_size  = 0;

    parameters->source    = input;
    parameters->start     = 0;
    parameters->current   = 0;
}


/*
 * @brief : Tells whether `current` points at the end ('\0')
 * @return: `true`, if yes
 */
bool
current_is_at_end(struct Parameters *parameters)
{
    char *source   = parameters->source;
    size_t current = parameters->current;

    if (source[current] == '\0') return true;

    return false;
}


/* 
 * @brief : Advances `current`
 * @return: Character previous to `current`
 */
char
advance_current(struct Parameters *parameters)
{
    parameters->current += 1;

    size_t current = parameters->current;
    char  *source  = parameters->source;

    return source[current - 1];
}


/* 
 * Returns `true` if the next char to `current` is `expected`.
 * Else returns `false`.
 */
bool
match(struct Parameters *parameters, char expected)
{
    char *source   = parameters->source;
    size_t current = parameters->current;

    if (source[current] == expected) return true;

    return false;
}


/* Initializes a `token` with default values. */
void
init_token(Token *token, Token_type type)
{
    token->type          = type;
    token->arg           = NULL;
    token->return_status = UNDEFINED;
}


/*
 * @brief : Creates a substring from a given string
 * @param : Pointer to original string; starting and terminating index of
 *          substring
 * @return: A `malloc`d array of substring
 */
char *
create_substring(char *string, size_t start, size_t end)
{
    /* Add `1` for null-byte */
    size_t buf_size = (end - start) + 1;
    char *substring = malloc(buf_size * sizeof(*substring));

    if (!substring) return NULL;

    string += start;  /* `string` ptr points to start of substring */
    memcpy(substring, string, buf_size - 1);
    substring[buf_size - 1] = '\0';

    return substring;
}


/*
 * @brief : Frees memory allocated to tokens if error occurs.
 * @param : A pointer to `struct Parameters`.
 */
void
free_tokens_on_error(struct Parameters *parameters)
{
    Token *tokens       = parameters->tokens;
    size_t tokens_count = parameters->arr_size - 1;

    free_tokens(tokens, tokens_count);
}
