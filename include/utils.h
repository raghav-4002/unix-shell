#ifndef UTILS_H
#define UTILS_H

#include "../include/lexer.h"
#include <stdlib.h>

void free_array_of_arrays (char **array, size_t array_size);
void free_elements (Element *elements);
void traverse_ast(Element *ast_root);

#endif
