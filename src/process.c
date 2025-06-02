#include "../include/process.h"
#include "../include/lexer.h"
#include "../include/utils.h"


void
process_and_execute(char *raw_input)
{
    char **tokens = NULL;
    size_t total_tokens;

    tokens = tokenize(raw_input, &total_tokens);

    /* syntax error occurs */
    if(tokens == NULL) {
        free_array_of_arrays(tokens, total_tokens);
        return;
    }

    // useful code will go here

    free_array_of_arrays(tokens, total_tokens);
}