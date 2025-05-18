#ifndef COMMAND_HANDLING_H
#define COMMAND_HANDLING_H


#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>


void handle_command(char **tokens);
void execute_command(char **tokens);


#endif