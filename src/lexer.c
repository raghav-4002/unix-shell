#include "../include/lexer.h"


Element *elements = NULL;
size_t elements_count = 0;


void
handle_command(char *string)
{
    elements = realloc(elements, sizeof(*elements) * (elements_count + 1));
    
    elements[elements_count].element_type = COMMAND;
    elements[elements_count].return_value = NOT_DEFINED_YET;

    elements[elements_count].command = NULL;
    size_t command_size = 0;

    while(1) {

    }
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
            handle_command(string);
        }
    }

    // Add a dummy at the end to signify no more elements
    elements = realloc(elements, sizeof(*elements) * (elements_count + 1));
    elements[elements_count].element_type = NIL;
    elements[elements_count].command = NULL;
    elements[elements_count].command_size = 0;
    elements[elements_count].return_value = NOT_DEFINED_YET;

    elements_count++;

    *total_elements = elements_count;
    return elements;
}