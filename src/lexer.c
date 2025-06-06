#include "../include/lexer.h"


Element *elements = NULL;
size_t elements_count = 0;


void
allocate_element_space(void)
{
    elements = realloc(elements, sizeof(*elements) * (elements_count + 1));
}


void
define_element(int element_type, int return_value)
{
    elements[elements_count].element_type = element_type;
    elements[elements_count].return_value = return_value;

    if(element_type != COMMAND) {
        elements[elements_count].command = NULL;
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

    total_tokens++;

    elements[elements_count].command = tokens;
}


void
handle_command(char **string)
{
    /* allocate space for one more element */
    allocate_element_space();
    define_element(COMMAND, NOT_DEFINED_YET);

    create_token(string);

    elements_count++;
}


void
handle_operand(int operand)
{
    allocate_element_space();

    define_element(operand, NOT_DEFINED_YET);

    elements_count++;
}


Element *
tokenize(char *raw_input, size_t *total_elements)
{
    char *string = raw_input;

    while(*string != '\0') {

        if(*string == '|') {
            if(string[1] != '|') {
                //handle error
            }
            handle_operand(LOGIC_OR);
            string = string + 2;
            continue;
        }

        if(*string == '&') {
            if(string[1] != '&') {
                //handle error
            }
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
            // skip space
            string++;
            continue;
        }

        // if(isalpha(*string)) {
        //     handle_command(&string);
        // }
        else {
            handle_command(&string);
        }
    }

    /* add a dummy element at the end to signify no more elements */
    allocate_element_space();

    define_element(NIL, NOT_DEFINED_YET);

    elements_count++;

    *total_elements = elements_count;
    return elements;
}