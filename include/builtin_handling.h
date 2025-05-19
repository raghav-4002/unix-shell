#ifndef BUILTIN_HANDLING_H
#define BUILTIN_HANDLING_H


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


void handle_builtin(char **tokens);
bool is_builtin(char *token);


#endif