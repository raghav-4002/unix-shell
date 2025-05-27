#include "../include/tokenization.h"


/*
 * Takes a string as an input, tokenizes the string by removing 
    semicolons and returns an array of array:.
*/
char **
remove_semicolons(char *raw_input, size_t *array_size)
{
    char **string_array = NULL;
    char *token = NULL;

    /* tokenize the string into multiple strings separeted by `;` */
    token = strtok(raw_input, ";");

    size_t i = 0;

    string_array = realloc(string_array, (i + 1) * sizeof(*string_array));
    string_array[i] = malloc(strlen(token) + 1);
    memcpy(string_array[i], token, strlen(token) + 1);

    i++;

    while(1) {
        token = strtok(NULL, ";");

        if(token == NULL) break;    // tokenization is complete

        string_array = realloc(string_array, (i + 1) * sizeof(*string_array));
        string_array[i] = malloc(strlen(token) + 1);
        memcpy(string_array[i], token, strlen(token) + 1);

        i++;
    }

    /* terminate the array of strings(commands) with NULL */
    string_array = realloc(string_array, (i + 1) * sizeof(*string_array));
    string_array[i] = NULL;

    *array_size = i + 1;   /* useful for freeing the memory allocated to `string_array`*/

    return string_array;
}


/*
 * Takes a string (`input`) and variable (`command_size`) and returns an array of strings (`tokens`),
   that are separated by `space` in the original `input` string.
 * Modifies the value of `command_size` to that of size of the returned array.
*/
char **
tokenize(char *string, int *command_size)
{
    char *token = NULL;             /* the individual token*/
    char **token_array = NULL;      /* all the tokens to return */
    *command_size = 0;              /* total number of tokens */

    token = strtok(string, " ");

    /* increment token count */
    *command_size = *command_size + 1;

    /* allocate memory to array */
    token_array = realloc(token_array, *command_size * sizeof(*token_array));

    /* allocate memory to store the string(token) */
    token_array[*command_size - 1] = malloc(strlen(token) + 1);

    /* move the contents of 'token' to the array of arrays */
    memcpy(token_array[*command_size - 1], token, strlen(token) + 1);

    while(1) {
        token = strtok(NULL, " ");
        if(token == NULL) break;            /* tokenization is complete */

        *command_size = *command_size + 1;
        token_array = realloc(token_array, *command_size * sizeof(*token_array));
        token_array[*command_size - 1] = malloc(strlen(token) + 1);
        memcpy(token_array[*command_size - 1], token, strlen(token) + 1);
    }

    /* append with NULL at the end of array */
    *command_size = *command_size + 1;
    token_array = realloc(token_array, *command_size * sizeof(*token_array));
    token_array[*command_size - 1] = NULL; 

    return token_array;
}