#include "../include/lexer.h"


Element *elements = NULL;
size_t element_index = 0;


void
allocate_and_define_elem(int element_type)
{
    /* `element_index` starts with 0, thus need to add `1` */
    elements = realloc(elements, sizeof(*elements) * (element_index + 1));

    elements[element_index].element_type = element_type;
    elements[element_index].return_value = NOT_DEFINED_YET; /* same for every element */

    if(element_type != COMMAND) {
        /* `COMMAND` type will have an array of strings */
        elements[element_index].tokens = NULL;
    }
}


size_t
find_token_length(char **string)
{
    char **ptr = string;
    size_t token_length = 0;

    while(
        **ptr != '\0' &&
        **ptr != '&'  &&
        **ptr != '|'  &&
        **ptr != ';'  &&
        **ptr != ' '
    ) {
        token_length++;
        (*ptr)++;
    }

    return token_length;
}


char **
create_tokens(char **string)
{
    char **tokens = NULL;
    size_t token_index = 0;

    while(1) {
        /*
         * A single instance of this loop will find a token
           and assign it to `tokens` array.
        */

        /* Add space for one more token */
        tokens = realloc(tokens, sizeof(*tokens) * (token_index + 1));

        size_t token_length = find_token_length(string);

        /* allocate memory for a single token; have added `1` to include null-byte */
        tokens[token_index] = malloc(token_length + 1);

        /* copy the contents of input into `tokens` array */
        memcpy(tokens[token_index], *string, token_length);
        
        /* add null byte at the end of the token */
        tokens[token_index][token_length] = '\0';

        token_index++;     // increment token count

        /* move the pointer */
        *string = *string + token_length;

        if(**string == ' ') {
            /* skip spaces */
            while(**string == ' ') {
                (*string)++;
            }
        }
        
        if(
            **string == '\0' ||
            **string == '&'  ||
            **string == '|'  ||
            **string == ';'
        ) break;
    }

    tokens = realloc(tokens, sizeof(*tokens) * (token_index + 1));
    tokens[token_index] = NULL;

    return tokens;
}


void
handle_command(char **string)
{
    /* allocate space for one more element */
    allocate_and_define_elem(COMMAND);

    elements[element_index].tokens = create_tokens(string);

    element_index++;
}


void
handle_operand(int operand)
{
    allocate_and_define_elem(operand);

    element_index++;
}


Element *
tokenize(char *raw_input)
{
    char *string = raw_input;

    while(*string != '\0') {

        if(*string == '|') {
            handle_operand(LOGIC_OR);
            string = string + 2;
            continue;
        }

        if(*string == '&') {
            handle_operand(LOGIC_AND);
            string = string + 2;
            continue;
        }

        if(*string == ';') {
            handle_operand(SEMICOLON);
            string++;
            continue;
        }

        if(isspace(*string)) {
            /* skip space */
            string++;
            continue;
        }

        else {
            handle_command(&string);
        }
    }

    /* add a dummy element at the end to signify no more elements */
    allocate_and_define_elem(NIL);

    return elements;
}