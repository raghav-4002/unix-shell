#ifndef BUILTIN_HANDLING_H
#define BUILTIN_HANDLING_H


#include <stdio.h>


extern const char *builtins[];
extern unsigned total_builtins;


void handle_builtin(char **tokens);


#endif