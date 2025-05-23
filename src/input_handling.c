#include "../include/input_handling.h"


/*
 * Takes a string as an input, and returns an array of commands, seperated by semicolons.
*/
char **
separate_commands(char *line)
{
    char **commands = NULL;
    char *token = NULL;

    /* tokenize the string into multiple strings separeted by `;` */
    token = strtok(line, ";");

    size_t i = 0;

    commands = realloc(commands, (i + 1) * sizeof(*commands));
    commands[i] = malloc(strlen(token) + 1);
    memcpy(commands[i], token, strlen(token) + 1);

    i++;

    while(1) {
        token = strtok(NULL, ";");

        if(token == NULL) break;    // tokenization is complete

        commands = realloc(commands, (i + 1) * sizeof(*commands));
        commands[i] = malloc(strlen(token) + 1);
        memcpy(commands[i], token, strlen(token) + 1);

        i++;
    }

    /* terminate the array of strings(commands) with NULL */
    commands = realloc(commands, (i + 1) * sizeof(*commands));
    commands[i] = NULL;

    return commands;
}


/*
 * Reads a line from the stdin and returns an array of strings (commands), if the 
   string contains semicolons.
*/
char **
read_input(void)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t line_len;

    /* read raw input from the commandline */
    line_len = getline(&line, &n, stdin);

    if(line_len == -1 || line_len == 1) {
        /* in case of error, or if user just presses enter */
        return NULL;
    }

    /* terminate the input with null byte, replacing newline char */
    line[line_len - 1] = '\0';

    /* make an array of commands, separated by semicolons */
    char **commands = separate_commands(line);

    free(line);    // no longer need this; read man page of `getline`, says to free `input`

    return commands;       // return the array of strings, where each string is a command
}


char **
tokenize_input(char *input, int *token_count)
{
    char *string = input;       /* the string to tokenize */
    char *token = NULL;         /* the individual token*/
    char **token_array = NULL;  /* all the tokens to return */
    *token_count = 0;           /* total number of tokens */


    token = strtok(string, " ;");

    /* increment token count */
    *token_count = *token_count + 1;

    /* allocate memory to array */
    token_array = realloc(token_array, *token_count * sizeof(*token_array));

    /* allocate memory to store the string(token) */
    token_array[*token_count - 1] = malloc(strlen(token) + 1);

    /* move the contents of 'token' to the array of arrays */
    memcpy(token_array[*token_count - 1], token, strlen(token) + 1);

    while(1) {
        token = strtok(NULL, " ;");
        if(token == NULL) break;            /* tokenization is complete */

        *token_count = *token_count + 1;
        token_array = realloc(token_array, *token_count * sizeof(*token_array));
        token_array[*token_count - 1] = malloc(strlen(token) + 1);
        memcpy(token_array[*token_count - 1], token, strlen(token) + 1);
    }

    /* append with NULL at the end of array */
    *token_count = *token_count + 1;
    token_array = realloc(token_array, *token_count * sizeof(*token_array));
    token_array[*token_count - 1] = NULL; 

    return token_array;
}