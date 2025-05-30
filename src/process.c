#include "../include/process.h"
#include "../include/lexer.h"


void
process_and_execute(char *raw_input)
{
    char **tokens = NULL;
    size_t total_tokens;
    tokens = tokenize(raw_input, &total_tokens);

    size_t i = 0;
    while(tokens[i] != NULL) {
        printf("|%s|\n", tokens[i]);
        i++;
    }
}