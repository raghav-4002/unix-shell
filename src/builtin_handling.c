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
handle_builtin(char **tokens)
{
    
}


bool
is_builtin(char *token)
{
    for (unsigned i = 0; i < builtins_count; i++) {
        if (!strcmp(builtins[i], token)) return true;
    }

    return false;
}