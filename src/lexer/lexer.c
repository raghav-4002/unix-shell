#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "lexer.h"
#include "token.h"
#include "lexer_helper.h"


void
add_arg(struct Parameters *parameters)
{
    char  *string = parameters->source;
    size_t start  = parameters->start;
    size_t end    = parameters->current;

    parameters->tokens->arg = create_substring(string, start, end);
}


void
add_token(struct Parameters *parameters, Token_type type)
{
    Token *tokens = parameters->tokens;

    /* Add space for one more token */
    parameters->arr_size += 1;
    size_t arr_size       = parameters->arr_size;
    size_t cur_index      = arr_size - 1;

    /* Resize array */
    tokens = realloc(tokens, arr_size * sizeof(*tokens));

    Token cur_token = tokens[cur_index];
    init_token(&cur_token, type);

    /* 
     * Necessary, otherwise `parameters->tokens` would
     * always remain `NULL`
     */
    if (!parameters->tokens) {
        parameters->tokens = tokens;
    }

    if (type == COMMAND) {
        add_arg(parameters);
    }
}


void
command(struct Parameters *parameters)
{
    /* Move current ahead, until any of the recognised lexeme is not found */
    while (!match(parameters, ' ') && !match(parameters, '\n')
           && !match(parameters, '\t') && !match(parameters, '\0')
           && !match(parameters, ';') && !match(parameters, '&')
           && !match(parameters, '|')) {

        advance(parameters);
    }

    add_token(parameters, COMMAND);
}


void
scan_token(struct Parameters *parameters)
{
    char c = advance(parameters);

    switch (c) {
        /* Single character tokens */
        case ';': add_token(parameters, SEMICOLON); break;

        /* Skip white spaces */
        case ' ': case '\t': case '\n': break;

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

        /* Command tokens */
        defalut:
            command(parameters);
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
    /*
     * Structure consisting of `parameters`
     * like array of `Token`, the source string 
     * to be tokenized, current and starting 
     * index of the source string .
     * This allows avoidance of global variables.
     */
    struct Parameters parameters;
    init_parameters(&parameters, input);

    while (!current_is_at_end(&parameters)) {
        /* Move to the next lexeme */
        parameters.start = parameters.current;
        scan_token(&parameters);
    }

    /* Add `NIL` as last token */
    add_token(&parameters, NIL);
    assert(parameters.tokens != NULL);

    return parameters.tokens;
}
