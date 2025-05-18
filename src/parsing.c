#include <stdbool.h>
#include <string.h>

#include "parsing.h"
#include "builtin_handling.h"
#include "command_handling.h"


bool
is_builtin(char *token)
{
    for (unsigned i = 0; i < total_builtins; i++) {
        if (!strcmp(builtins[i], token)) return true;
    }

    return false;
}


void
parse_and_execute(char **tokens)
{
    if (is_builtin(tokens[0])) {
        handle_builtin(tokens);
    } else {
        handle_command(tokens);
    }
}