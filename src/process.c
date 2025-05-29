#include "../include/process.h"
#include "../include/lexer.h"


void
process_and_execute(char *raw_input)
{
    char **tokens = NULL;
    tokens = tokenize(raw_input, NULL);
}