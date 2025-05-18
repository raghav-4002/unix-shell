#include <stdlib.h>
#include <stdio.h>

#include "input_handling.h"
#include "parsing.h"


void
free_memory(char *input, char **tokens, int token_count)
{
    /* free memory allocated by 'read_input' */
    free(input);
    input = NULL;

    /* free memory allocated by 'tokenize_input */
    for(int i = 0; i < token_count; i++) {
        free(tokens[i]);
    }

    free(tokens);
    tokens = NULL;
}


int
main(void)
{
    char *input = NULL;
    char **tokens = NULL;
    int token_count;

    while(1) {
        printf("seash> ");

        input = read_input();
        if(input == NULL) {
            fprintf(stderr, "Line reading failed...\n");
            continue;
        }

        tokens = tokenize_input(input, &token_count);

        parse_and_execute(tokens);

        /* free the memory allocated by read_input function */
        free_memory(input, tokens, token_count);
    }

    return EXIT_SUCCESS;
}