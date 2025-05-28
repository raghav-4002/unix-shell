#ifndef TOKENIZATION_H
#define TOKENIZATION_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char **remove_semicolons(char *raw_input, size_t *array_size);
char **tokenize(char *raw_input, size_t *total_tokens);


#endif