#include "../include/process.h"
#include "../include/builtin_handling.h"
#include "../include/exec_handling.h"
#include "../include/utils.h"


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


/*
 * Takes `commands_array`, array of strings where each string is an unprocessed command.
   Tokenizes each string into commands, checks whether each command is a builtin or an 
   executable and passes on the control to respective functions.
*/
void
process_and_execute(char **commands_array)
{
    char **command = NULL;
    int command_size = 0;
    size_t i = 0;

    /* take each string, tokenize it and then execute it */
    while(commands_array[i] != NULL) {
        command = tokenize_commands(commands_array[i], &command_size);

        /* check if its builtin or executable */
        if(is_builtin(command[0])) {
            handle_builtin(command);
        } else {
            handle_exec(command);
        }

        free_array_of_arrays(command, command_size);

        i++;
    }
}