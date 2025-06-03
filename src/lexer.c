#include "../include/lexer.h"


Element *elements = NULL;
size_t elements_count = 0;
size_t i = 0;


void
handle_operand(int operand)
{
    elements = realloc(elements, elements_count + 1);

    elements[elements_count].element_type = operand;
    elements[elements_count].command = NULL;
    elements[elements_count].command_size = 0;
    elements[elements_count].return_value = NOT_DEFINED_YET;

    elements_count++;
}


Element 
*tokenize(char *raw_input, size_t *total_elements)
{
    while(raw_input[i] != '\0') {

        if(raw_input[i] == '|') {
            if(raw_input[i + 1] != '|') {
                //handle error
            }
            handle_operand(LOGIC_OR);
            i = i + 2;
            continue;
        }

        if(raw_input[i] == '&') {
            if(raw_input[i + 1] != '&') {
                //handle error
            }
            handle_operand(LOGIC_AND);
            i = i + 2;
            continue;
        }

        if(raw_input[i] == ';') {
            handle_operand(SEMICOLON);
            i++;
            continue;
        }
    }
        
    return NULL;
}