#include "builtin_handling.h"
#include <stddef.h>


/* all supported builtins; some are under construction... */
const char *builtins[] = {
    "cd", 
    "exit", 
    "history", 
    "help",
    "exec",
};

size_t builtins_count = sizeof(builtins) / sizeof(builtins[0]);


void
change_dir(char **tokens)
{
    printf("cd underconstructioin...\n");
}


void
execute_and_exit(char **tokens)
{
    /* make a copy of tokens, ignoring 'exec' */
    char **executable = &tokens[1];
    execvp(executable[0], executable);
}


void
handle_builtin(char **tokens)
{
    if (!strcmp(tokens[0], "cd"))
        change_dir(tokens);

    else if (!strcmp(tokens[0], "exit"))
        exit(EXIT_SUCCESS);         /* simply exit the program */

    else if (!strcmp(tokens[0], "exec"))
        execute_and_exit(tokens);
}


bool
is_builtin(char *token)
{
    for (size_t i = 0; i < builtins_count; i++) {
        if (!strcmp(builtins[i], token)) return true;
    }

    return false;
}