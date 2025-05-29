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
    char *p = raw_input;

    while(*p != '\0') {
        if(isalpha(*p)) {
            // manage characters

            continue;
        }

        if(isspace(*p)) {
            p++;
            continue;
        }
    
        if(p[0] == '&' && p[1] == '&') {
            // manage ampersand
            continue;
        }

        if(p[0] == '|' && p[1] == '|') {
            // manage pipe
            continue;
        }

        if(*p == ';') {
            // manage semicolon
            continue;
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