#include "builtin_handling.h"


const char *builtins[] = {
    "cd", 
    "exit", 
    "history", 
    "help",
    "exec",
};

unsigned builtins_count = sizeof(builtins) / sizeof(builtins[0]);


void
change_dir(char **tokens)
{
    printf("Working on cd...\n");
}


void
execute_and_exit(char **tokens)
{
    tokens = &tokens[1];
    execvp(tokens[0], tokens);
}


void
handle_builtin(char **tokens)
{
    if (!strcmp(tokens[0], "cd"))
        change_dir(tokens);

    else if (!strcmp(tokens[0], "exit"))
        exit(EXIT_SUCCESS);

    else if (!strcmp(tokens[0], "exec"))
        execute_and_exit(tokens);
}


bool
is_builtin(char *token)
{
    for (unsigned i = 0; i < builtins_count; i++) {
        if (!strcmp(builtins[i], token)) return true;
    }

    return false;
}