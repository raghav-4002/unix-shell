#include "../include/lexer.h"
#include <ctype.h>
#include <stddef.h>


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

    char *p = raw_input;

    while(*p != '\0') {

        if(isalpha(*p)) {
            /* allocate one more memory space to `tokens` array */
            tokens = realloc(tokens, token_count + 1);
            
            /* initialize with NULL to make realloc work inside do-while loop */
            tokens[token_count] = NULL;
            size_t i = 0;

            do {
                /* allocate memory to insert one more character */
                tokens[token_count] = realloc(tokens[token_count], i + 1);

                tokens[token_count][i] = *p;

                i++; /* increment index */
                p++; /* move to the next character */
            } while(isalpha(*p));

            /* insert null-byte at the end */
            tokens[token_count] = realloc(tokens, token_count + 1);
            tokens[token_count][i] = '\0';

            /* one more token added */
            token_count++;

            continue;
        }

        if(isspace(*p)) {
            /* skip whitespace */
            p++;
            continue;
        }
    
        if(p[0] == '&' && p[1] == '&') {
            /* allocate more memory to `tokens` array */
            tokens = realloc(tokens, token_count + 1);

            /* allocate 3 bytes: 2 for '&&' and one for '\0' */
            tokens[token_count] = malloc(3);

            /* strlen("&&") = 2; add 1 for including null-byte too */
            memcpy(tokens[token_count], "&&", strlen("&&") + 1);
            
            token_count++;

            /* move 2 steps ahead */
            p = p + 2;

            continue;
        }

        if(p[0] == '|' && p[1] == '|') {
            /* allocate more memory to `tokens` array */
            tokens = realloc(tokens, token_count + 1);

            /* allocate 3 bytes: 2 for '||' and one for '\0' */
            tokens[token_count] = malloc(3);

            /* strlen("||") = 2; add 1 for including null-byte too */
            memcpy(tokens[token_count], "||", strlen("||") + 1);

            token_count++;

            /* move 2 steps ahead */
            p = p + 2;

            continue;
        }

        if(*p == ';') {
            tokens = realloc(tokens, token_count + 1);

            /* 2 bytes: 1 byte for `;` + 1 byte for '\0' */
            tokens[token_count] = malloc(2);

            /* strlen(";") = 1; add 1 for including null-byte */
            memcpy(tokens[token_count], ";", strlen(";") + 1);

            token_count++;

            /* move a single step ahead */
            p++;

            continue;
        }
    }

    tokens[token_count] = realloc(tokens, token_count + 1);
    tokens[token_count] = NULL;
    token_count++;

    *total_tokens = token_count;

    return tokens;
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