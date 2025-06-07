#ifndef COMMAND_HANDLING_H
#define COMMAND_HANDLING_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void handle_exec (char **tokens);
void execute (char **tokens);

#endif