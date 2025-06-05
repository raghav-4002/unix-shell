#ifndef UTILS_H
#define UTILS_H


#include <stdlib.h>
#include "../include/lexer.h"


void free_array_of_arrays(char **array, size_t array_size);
void free_elements(Element *elements, size_t total_elements);


#endif