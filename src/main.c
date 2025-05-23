#include "../include/input_handling.h"
#include "../include/parsing.h"


void
free_memory(char *input, char **tokens, int token_count)
{
    /* free memory allocated by 'read_input' */
    free(input);
    input = NULL;

    /* free memory allocated by 'tokenize_input' */
    for(int i = 0; i < token_count; i++) {
        free(tokens[i]);
    }

    free(tokens);
    tokens = NULL;
}


void
display_prompt(void)
{
    char *username;
    username = getlogin();

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    char working_dir[256];
    getcwd(working_dir, sizeof(working_dir));

    printf("{%s on %s}-[%s]: ", username, hostname, working_dir);
}


int
main(void)
{
    char *input = NULL;
    char **tokens = NULL;
    int token_count;

    while(1) {
        display_prompt();

        input = read_input();
        if(input == NULL) {
            /* if user only presses enter or if line reading fails */
            continue;
        }

        tokens = tokenize_input(input, &token_count);

        parse_and_execute(tokens);

        /* free the memory allocated by read_input function */
        free_memory(input, tokens, token_count);
    }

    return EXIT_SUCCESS;
}