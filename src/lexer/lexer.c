#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "lexer.h"
#include "token.h"
#include "lexer_helper.h"


int
add_arg(struct Parameters *parameters)
{
    char  *string = parameters->source;
    size_t start  = parameters->start;
    size_t end    = parameters->current;

    parameters->tokens->arg = create_substring(string, start, end);

    if (!parameters->tokens->arg) return -1;

    return 0;
}


int
add_token(struct Parameters *parameters, Token_type type)
{
    Token *tokens = parameters->tokens;

    /* Add space for one more token */
    parameters->arr_size += 1;
    size_t arr_size       = parameters->arr_size;
    size_t cur_index      = arr_size - 1;

    /* Resize array */
    tokens = realloc(tokens, arr_size * sizeof(*tokens));

    if (!tokens) {
        parameters->arr_size -= 1;  /* reset array size */
        return -1;
    }

    Token *cur_token = &tokens[cur_index];
    init_token(cur_token, type);

    /* 
     * Necessary, otherwise `parameters->tokens` would
     * always remain `NULL`
     */
    if (!parameters->tokens) {
        parameters->tokens = tokens;
    }

    if (type == COMMAND) {
        if (add_arg(parameters) == -1) return -1;
    }

    return 0;
}


int
command(struct Parameters *parameters)
{
    /* Move current ahead, until any of the recognised lexeme is not found */
    while (!match(parameters, ' ') && !match(parameters, '\n')
           && !match(parameters, '\t') && !match(parameters, '\0')
           && !match(parameters, ';') && !match(parameters, '&')
           && !match(parameters, '|')) {

        advance(parameters);
    }

    int err_return = add_token(parameters, COMMAND);

    return err_return;
}


int
scan_token(struct Parameters *parameters)
{
    char c = advance(parameters);

    int err_return = 0;

    switch (c) {
        /* Single character tokens */
        case ';':
            err_return = add_token(parameters, SEMICOLON);
            break;

        case ' ': case '\n': case '\t':
            break;

        /* Double/single character tokens */
        case '|':
            if (match(parameters, '|')) {
                err_return = add_token(parameters, LOGIC_OR);
            }
            else {
                err_return = add_token(parameters, PIPE);
            }
            break;

        case '&':
            if (match(parameters, '&')) {
                err_return = add_token(parameters, LOGIC_AND);
            }
            else {
                err_return = add_token(parameters, BG_OPERATOR);
            }
            break;

        /* Command tokens */
        default:
            err_return = command(parameters);
            break;
    }

    if (err_return == -1) return -1;

    return 0;
}


/*
 * @brief : Tokenizes an input string; stops when encounters `\0`
 * @param : An input string
 * @return: An array of type `Token`; last element is type `NIL`
 *          `NULL` on failure
 */
Token *
tokenize(char *input)
{
    /*
     * Structure consisting of `parameters`
     * like array of `Token`, the source string 
     * to be tokenized, current and starting 
     * index of the source string .
     * This allows avoidance of global variables
     * because globals bad ;)
     */
    struct Parameters parameters;
    init_parameters(&parameters, input);

    int err_return = 0;

    while (!current_is_at_end(&parameters)) {
        /* Move to the next lexeme */
        parameters.start = parameters.current;
        err_return       = scan_token(&parameters);

        if (err_return == -1) return NULL;
    }

    /* Add `NIL` as last token */
    err_return = add_token(&parameters, NIL);
    if (err_return == -1) return NULL;

    assert(parameters.tokens != NULL);

    return parameters.tokens;
}
