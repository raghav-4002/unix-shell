#ifndef INPUT_HANDLING_H
#define INPUT_HANDLING_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char **read_input(size_t *commands_count);
char **tokenize_input(char *input, int *token_count);


#endif