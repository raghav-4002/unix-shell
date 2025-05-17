#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "input_handling.h"


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


void
execute_command(char **tokens)
{
    execvp(tokens[0], tokens);
}


void
hanlde_command(char **tokens)
{
    /* create a child process */
    pid_t pid = fork();

    if(pid == 0) {
        execute_command(tokens);
    } else {
        wait(NULL);
    }
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
        tokens = tokenize_input(input, &token_count);

        hanlde_command(tokens);

        /* free the memory allocated by read_input function */
        free_memory(input, tokens, token_count);
    }

    return EXIT_SUCCESS;
}