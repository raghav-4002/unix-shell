#include "utils.h"
#include "lexer/token.h"


void
free_tokens(Token *tokens, size_t tokens_count)
{
    for (size_t i = 0; i < tokens_count; i++) {
        if (tokens[i].type == COMMAND) {
            free(tokens[i].arg);
        }
    }

    free(tokens);
}
