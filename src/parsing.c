#include "parsing.h"
#include "builtin_handling.h"
#include "command_handling.h"


void
parse_and_execute(char **tokens)
{
    if (is_builtin(tokens[0])) {
        handle_builtin(tokens);
    } else {
        handle_command(tokens);
    }
}