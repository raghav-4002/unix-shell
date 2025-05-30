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
    /*
     * Pointer `p` traverses thru. the string.

     * If it encounters an alphabatic character,
       it will copy the whole word (succeding 
       the character) as a token.

     * If it encounters `&` or `|`, it will check
       whether the next character is also the same.
       If it is, then another token (`&&` or `||`)
       will be added.

     * If it sees space, it will just skip over it.

     * It will also add `;` as the token, if it encounters
       one.

     * When all tokens are added, a `NULL` will be appended
       in the last of the array, to signify no more tokens.
    */

    char **tokens = NULL;
    size_t token_count = 0;

    char *p = raw_input;

    while(*p != '\0') {

        if(isalpha(*p) || *p == '-') {

            /* `token_count` is always 1 less than actual tokens count */
            tokens = realloc(tokens, token_count + 1);

            /* initialize with NULL to make realloc work in the proceeding while loop */
            tokens[token_count] = NULL;
            size_t i = 0;
            
            do {
                tokens[token_count] = realloc(tokens[token_count], i + 1);
                tokens[token_count][i] = *p;
                i++;
                p++;
            } while(isalpha(*p));

            /* now add a null byte at the end of token */
            tokens[token_count] = realloc(tokens[token_count], i + 1);
            tokens[token_count][i] = '\0';

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

    /* add `NULL` as the last token, to signify no more tokens */
    tokens = realloc(tokens, token_count + 1);
    tokens[token_count] = NULL;
    token_count++;

    *total_tokens = token_count;

    return tokens;
}