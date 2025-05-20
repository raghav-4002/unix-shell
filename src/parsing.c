#include "../include/parsing.h"
#include "../include/builtin_handling.h"
#include "../include/command_handling.h"


void
parse_semicolons(char **tokens)
{
    /* check for semi-colons and replace them with NULL */
    size_t i = 0;

    while(tokens[i] != NULL) {
        if(!strcmp(tokens[i], ";")) {
            tokens[i] = NULL;
        }

        i++;
    }
}


void
parse_and_execute(char **tokens)
{
    parse_semicolons(tokens);

    if (is_builtin(tokens[0])) {
        handle_builtin(tokens);
    } else {
        handle_command(tokens);
    }
}