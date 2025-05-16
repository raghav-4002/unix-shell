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

    token = strtok(string, " ");
    while(token != NULL) {
        token = strtok(NULL, " ");
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