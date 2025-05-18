#include <stdio.h>

#include "builtin_handling.h"


const char *builtins[] = {"cd", "exit", "history", "help"};
unsigned total_builtins = sizeof(builtins) / sizeof(builtins[0]);


void
handle_builtin(char **tokens)
{
    printf("Builtin handled!!!\n");
}