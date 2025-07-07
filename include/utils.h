#ifndef UTILS_H
#define UTILS_H

#include "../include/lexer.h"
#include <stdlib.h>

void free_tokens (Token **tokens);
void traverse_ast (Token *ast_root);

#endif
