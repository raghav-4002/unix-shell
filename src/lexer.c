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
    char *string = NULL;

    while(*p != '\0') {
        /* logic for separating tokens */
        if(isalpha(*p)) {
            // handle alphabets
            tokens = realloc(tokens, token_count + 1);
            tokens[token_count] = NULL;

            size_t i = 0;

            while(isalpha(*p)) {
                tokens[token_count] = realloc(tokens[token_count], i + 1);
                tokens[token_count][i] = *p;
                i++;
                p = p + 1;
            }

            tokens[token_count] = realloc(tokens[token_count], i + 1);
            tokens[token_count][i] = '\0';

            token_count++;
            
            continue;
        }

        if(*p == ' ') {
            // handle space
            continue;
        }

        if(*p == '|') {
            // handle pipe 
            continue;
        }

        if(*p == '&') {
            // handle ampersand
            continue;
        }

        if(*p == ';') {
            // handle semi colons
            continue;
        }
    }
    
    // add logic to add NULL at the end of `tokens_array`
    tokens = realloc(tokens, token_count + 1);
    tokens[token_count] = NULL;

    return tokens;
}