#ifndef COMMAND_HANDLING_H
#define COMMAND_HANDLING_H

#include "lexer.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void handle_exec (Token *node);

#endif
