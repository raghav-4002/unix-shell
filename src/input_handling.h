#ifndef INPUT_HANDLING_H
#define INPUT_HANDLING_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_input(void);
char **tokenize_input(char *input, int *token_count);


#endif