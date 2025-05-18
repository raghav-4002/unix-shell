#include "input_handling.h"


char *
read_input(void)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t line_len;

    /* read input line */
    line_len = getline(&line, &n, stdin);
    if (line_len == -1) {
        /* in case of getline failing */
        return NULL;
    }

    /* add null byte at the end */
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

    /* append with NULL at the end of array; necessary for 'execvp' function */
    *token_count = *token_count + 1;
    token_array = realloc(token_array, *token_count * sizeof(*token_array));
    token_array[*token_count - 1] = NULL; 

    return token_array;
}