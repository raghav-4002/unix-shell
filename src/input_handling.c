#include "../include/input_handling.h"


/*
 * Takes a string as an input, and returns an array of commands, seperated by semicolons.
*/
char **
separate_commands(char *line)
{
    char **commands_array = NULL;
    char *token = NULL;

    /* tokenize the string into multiple strings separeted by `;` */
    token = strtok(line, ";");

    size_t i = 0;

    commands_array = realloc(commands_array, (i + 1) * sizeof(*commands_array));
    commands_array[i] = malloc(strlen(token) + 1);
    memcpy(commands_array[i], token, strlen(token) + 1);

    i++;

    while(1) {
        token = strtok(NULL, ";");

        if(token == NULL) break;    // tokenization is complete

        commands_array = realloc(commands_array, (i + 1) * sizeof(*commands_array));
        commands_array[i] = malloc(strlen(token) + 1);
        memcpy(commands_array[i], token, strlen(token) + 1);

        i++;
    }

    /* terminate the array of strings(commands) with NULL */
    commands_array = realloc(commands_array, (i + 1) * sizeof(*commands_array));
    commands_array[i] = NULL;

    return commands_array;
}


/*
 * Reads a line from the stdin and returns an array of strings (commands), if the 
   string contains semicolons. Last element of array is NULL.
*/
char **
read_input(void)
{
    char *raw_input = NULL;
    size_t n = 0;
    ssize_t line_len;

    /* read raw input from the commandline */
    line_len = getline(&raw_input, &n, stdin);

    if(line_len == -1 || line_len == 1) {
        /* in case of error, or if user just presses enter */
        return NULL;
    }

    /* terminate the input with null byte, replacing newline char */
    raw_input[line_len - 1] = '\0';

    /* make an array of commands, separated by semicolons */
    char **commands_array = separate_commands(raw_input);

    free(raw_input);    // no longer need this; read man page of `getline`, says to free `input`

    return commands_array;       // return the array of strings, where each string is a command
}