#include "../include/lexer.h"


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
 * Takes a string (`raw_input`) and variable (`total_tokens`) and returns an array of strings (`tokens`),
   that are separated by `space` or `&&` or `||` in the original `raw_input` string. Adds `NULL` at the
   end of the returned array.

 * Modifies the value of `total_tokens` to that of size of the returned array. This count is useful for 
   freeing the dynamically allocated memory.
*/
char **
tokenize(char *raw_input, size_t *total_tokens)
{
    size_t i = 0, j = 0;

    while (raw_input[i] != '\0') {
        if (!isalpha(raw_input[j])) {

            switch(raw_input[j]) {
                case '&':
                    // do something with ampersand
                    break;

                case '|':
                    // do something with pipe
                    break;

                case ';':
                    // do something with semicolon
                    break;

                case '\0':
                    // do something with null byte
                    break;

                default:
                    fprintf(stderr, "Unrecognised token: %c\n",
                                            raw_input[j]);

                    break;
            }

        } else {
            
            /*
             * If the encountered character is an alphabet,
               simply increment `j`.
            */
            j++;
        }
    }
}



// char **
// tokenize(char *raw_input, size_t *total_tokens)
// {
//     char *single_token = NULL;       /* the individual token*/
//     char **tokens = NULL;            /* all the tokens to return */
//     *total_tokens = 0;               /* total number of tokens */

//     single_token = strtok(raw_input, " ");

//     while(single_token != NULL) {
//         /* increment tokens count */
//         *total_tokens = *total_tokens + 1;

//         /* allocate memory to `tokens` array */
//         tokens = realloc(tokens, *total_tokens * sizeof(*tokens));

//         /* allocate memory to element of `tokens` array */
//         tokens[*total_tokens - 1] = malloc(strlen(single_token) + 1);
        
//         /* copy the contents */
//         memcpy(tokens[*total_tokens - 1], single_token, strlen(single_token) + 1);

//         /* move to next token, is NULL if no delimiter found */
//         single_token = strtok(NULL, " ");
//     }

//     /* append with NULL at the end of array */
//     *total_tokens = *total_tokens + 1;
//     tokens = realloc(tokens, *total_tokens * sizeof(*tokens));
//     tokens[*total_tokens - 1] = NULL; 

//     return tokens;
// }