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