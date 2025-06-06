#include "../include/lexer.h"


Element *elements = NULL;
size_t element_index = 0;


void
allocate_and_define_elem(int element_type)
{
    /* element allocation */
    elements = realloc(elements, sizeof(*elements) * (element_index + 1));

    /* Initialization of `element_type`, `return_value`, and optionally `command` */
    elements[element_index].element_type = element_type;
    elements[element_index].return_value = NOT_DEFINED_YET;

    if(element_type != COMMAND) {
        elements[element_index].command = NULL;
    }
}


size_t
find_token_length(char **ptr)
{
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


void
create_token(char **string)
{
    char **tokens = NULL;
    size_t total_tokens = 0;

    while(1) {
        /*
         * A single instance of this loop will find a token
           and assign it to `tokens` array.
        */

        /* Add space for one more token */
        tokens = realloc(tokens, sizeof(*tokens) * (total_tokens + 1));

        char *ptr = *string;

        size_t token_length = find_token_length(&ptr);

        /* allocate memory for a single token; have added `1` to include null-byte */
        tokens[total_tokens] = malloc(token_length + 1);

        /* copy the contents of input into `tokens` array */
        memcpy(tokens[total_tokens], *string, token_length);
        
        /* add null byte at the end of the token */
        tokens[total_tokens][token_length] = '\0';

        total_tokens++;     // increment token count

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
    tokens = realloc(tokens, sizeof(*tokens) * (total_tokens + 1));
    tokens[total_tokens] = NULL;


    elements[element_index].command = tokens;
}


void
handle_command(char **string)
{
    /* allocate space for one more element */
    allocate_and_define_elem(COMMAND);

    create_token(string);

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