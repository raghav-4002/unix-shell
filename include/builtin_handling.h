#ifndef BUILTIN_HANDLING_H
#define BUILTIN_HANDLING_H

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handle_builtin (char **tokens);
bool is_builtin (char *token);

#endif