#include "../include/process.h"
#include "../include/lexer.h"


void
process_and_execute(char *raw_input)
{
    tokenize(raw_input, NULL);
}