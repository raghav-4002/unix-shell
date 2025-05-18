#ifndef BUILTIN_HANDLING_H
#define BUILTIN_HANDLING_H


#include <stdio.h>
#include <stdbool.h>
#include <string.h>


void handle_builtin(char **tokens);
bool is_builtin(char *token);


#endif