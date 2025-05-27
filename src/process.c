#include "../include/process.h"
#include "../include/tokenization.h"


/*
 * Takes a string (`input`) and variable (`command_size`) and returns an array of strings (`tokens`),
   that are separated by `space` in the original `input` string.
 * Modifies the value of `command_size` to that of size of the returned array.
*/
char **
tokenize_commands(char *input, int *command_size)
{
    char *string = input;       /* the string to tokenize */
    char *token = NULL;         /* the individual token*/
    char **command = NULL;      /* all the tokens to return */
    *command_size = 0;          /* total number of tokens */


    token = strtok(string, " ;");

    /* increment token count */
    *command_size = *command_size + 1;

    /* allocate memory to array */
    command = realloc(command, *command_size * sizeof(*command));

    /* allocate memory to store the string(token) */
    command[*command_size - 1] = malloc(strlen(token) + 1);

    /* move the contents of 'token' to the array of arrays */
    memcpy(command[*command_size - 1], token, strlen(token) + 1);

    while(1) {
        token = strtok(NULL, " ;");
        if(token == NULL) break;            /* tokenization is complete */

        *command_size = *command_size + 1;
        command = realloc(command, *command_size * sizeof(*command));
        command[*command_size - 1] = malloc(strlen(token) + 1);
        memcpy(command[*command_size - 1], token, strlen(token) + 1);
    }

    /* append with NULL at the end of array */
    *command_size = *command_size + 1;
    command = realloc(command, *command_size * sizeof(*command));
    command[*command_size - 1] = NULL; 

    return command;
}


void
process_and_execute(char *raw_input)
{
    // remove semicolons and create an array of strings
    char **string_array = NULL;
    size_t array_size = 0;

    string_array = remove_semicolons(raw_input, &array_size);
    
    // 2. Take each token and again process it, checking
    //    for && or ||.
}