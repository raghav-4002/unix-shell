#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void
free_memory(char *input, char **tokens, int token_count)
{
    /* free memory allocated by 'read_input' */
    free(input);

    /* free memory allocated by 'tokenize_input */
    for(int i = 0; i < token_count; i++) {
        free(tokens[i]);
    }

    free(tokens);
}


char *
read_input(void)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t line_len;

    /* read input line */
    line_len = getline(&line, &n, stdin);

    /* add null byte at the end, in place of newline */
    line[line_len - 1] = '\0';

    return line;
}


char **
tokenize_input(char *input, int *token_count)
{
    char *string = input;       /* the string to tokenize */
    char *token = NULL;         /* the individual token*/
    char **token_array = NULL;  /* all the tokens to return */
    *token_count = 0;           /* total number of tokens */


    token = strtok(string, " ");

    /* increment token count */
    *token_count = *token_count + 1;
    /* allocate memory to array */
    token_array = realloc(token_array, *token_count * sizeof(*token_array));
    /* allocate memory to store the string(token) */
    token_array[*token_count - 1] = malloc(strlen(token) + 1);
    /* move the contents of 'token' to the array of arrays */
    memcpy(token_array[*token_count - 1], token, strlen(token) + 1);

    while(1) {
        token = strtok(NULL, " ");
        if(token == NULL) break;            /* tokenization is complete */

        *token_count = *token_count + 1;
        token_array = realloc(token_array, *token_count * sizeof(*token_array));
        token_array[*token_count - 1] = malloc(strlen(token) + 1);
        memcpy(token_array[*token_count - 1], token, strlen(token) + 1);
    }

    return token_array;
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
    char *input;
    char **tokens;
    int token_count;

    while(1) {
        input = NULL;
        tokens = NULL;

        printf("seash> ");
        input = read_input();
        tokens = tokenize_input(input, &token_count);

        hanlde_command(tokens);

        /* free the memory allocated by read_input function */
        free_memory(input, tokens, token_count);
    }

    return EXIT_SUCCESS;
}