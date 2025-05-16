#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
tokenize_input(char *input)
{
    char *string = input;
    char *token = NULL;
    char **token_array = NULL;
    int token_count = 0;


    token = strtok(string, " ");

    token_count++;
    token_array = realloc(token_array, token_count * sizeof(*token_array));
    token_array[token_count - 1] = malloc(strlen(token) + 1);
    memcpy(token_array[token_count - 1], token, strlen(token) + 1);

    while(1) {
        token = strtok(NULL, " ");
        if(token == NULL) break;

        token_count++;
        token_array = realloc(token_array, token_count * sizeof(*token_array));
        token_array[token_count - 1] = malloc(strlen(token) + 1);
        memcpy(token_array[token_count - 1], token, strlen(token) + 1);
    }
}


int
main(void)
{
    char *input;
    char **tokens;

    while(1) {
        input = NULL;
        tokens = NULL;

        printf("seash> ");
        input = read_input();
        tokens = tokenize_input(input);

        /* free the memory allocated by read_input function */
        free(input);
    }

    return EXIT_SUCCESS;
}