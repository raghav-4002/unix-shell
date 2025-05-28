#include "../include/lexer.h"


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
    char **tokens = NULL;
    size_t token_count = 0;
    
    /* variables to traverse through the string */
    size_t i = 0, j = 0;

    while (1) {
        if (!isalpha(raw_input[j])) {

            /*
             * If encountered character is not an alphabet, 
               then first add the token from `i` to `j - 1` 
               into the `tokens` array and the proceed.
            */

            size_t total_bytes = i - j;     /* token size in bytes */

            /* allocate memory to array for holding another token */
            tokens = realloc(tokens, token_count + 1);

            /* allocate memory to hold the token itself */
            tokens[token_count] = malloc(total_bytes + 1);

            /* copy the contents, from `i` to `j - 1` */
            memcpy(tokens[token_count], &raw_input[i], total_bytes);
            
            /* increment token count */
            token_count++;
            

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
                    exit(EXIT_FAILURE);

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