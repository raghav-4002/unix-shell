#include "../include/input_handling.h"
#include "../include/process.h"


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
    char **commands_array = NULL;

    while(1) {
        display_prompt();

        commands_array = read_input();
        if(commands_array == NULL) {
            /* in case of error or user pressing enter, just continue the loop */
            continue;
        }

        process_and_execute(commands_array);
    }

    return EXIT_SUCCESS;
}