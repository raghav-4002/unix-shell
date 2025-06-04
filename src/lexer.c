#include "../include/lexer.h"


Element *elements = NULL;
size_t elements_count = 0;


void
handle_command(char **string)
{
    /* allocate space for one more element */
    elements = realloc(elements, sizeof(*elements) * (elements_count + 1));
    
    elements[elements_count].element_type = COMMAND;
    
    /* two dummy variables to manage tokens */
    char **command = NULL;
    size_t command_size = 0;

    while(1) {
        /* allocate one more space for another token */
        command = realloc(command, sizeof(*command) * (command_size + 1));

        /* `string_len` is just the size of a single token */
        size_t string_len = 0;
        
        char *ptr = *string;

        while (
            *ptr != '\0' &&
            *ptr != '&'  &&
            *ptr != '|'  &&
            *ptr != ';'  &&
            *ptr != ' '
        ) {
            string_len++;
            ptr++;        // move to next character of string
        }

        /* allocate memory for a single token; have added `1` to include null-byte */
        command[command_size] = malloc(string_len + 1);

        /* copy the contents of the token */
        memcpy(command[command_size], string, string_len);
        
        /* add null byte at the end */
        command[command_size][string_len] = '\0';

        command_size++;     // increment token count

        /* move the pointer */
        *string = *string + string_len;

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

    /* add a `NULL` as the last token */
    command = realloc(command, sizeof(*command) * (command_size + 1));
    command[command_size] = NULL;

    command_size++;

    elements[elements_count].command = command;
    elements[elements_count].command_size = command_size;

    elements_count++;
}


void
handle_operand(int operand)
{
    elements = realloc(elements, sizeof(*elements) * (elements_count + 1));

    elements[elements_count].element_type = operand;
    elements[elements_count].command = NULL;
    elements[elements_count].command_size = 0;
    elements[elements_count].return_value = NOT_DEFINED_YET;

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

        if(isalpha(*string)) {
            handle_command(&string);
        }
    }

    /* add a dummy element at the end to signify no more elements */
    elements = realloc(elements, sizeof(*elements) * (elements_count + 1));
    elements[elements_count].element_type = NIL;
    elements[elements_count].command = NULL;
    elements[elements_count].command_size = 0;
    elements[elements_count].return_value = NOT_DEFINED_YET;

    elements_count++;

    *total_elements = elements_count;
    return elements;
}