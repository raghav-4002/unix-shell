#include "../include/parser.h"

void
parse_pipeline(void)
{

}

void
parse_condition(void)
{

}

Element *
parse_sequence(Element *elements)
{
    /* logic to find positions of semicolons */
    size_t position_of_colons[100];
    size_t index = 1;

    for(size_t i = 0; elements[i].element_type != NIL; i++) {
        if(elements[i].element_type == NEXT) {
            position_of_colons[index] = i;
            index++;
        }
    }

    /* the last semi colon will be root */
    Element *root = &elements[index];

    /* now create a tree out of these semicolons */
    while(index != 0) {
        if(index != 1) {
            elements[index].left = &elements[index - 1];
        } else {
            /* special case for the first semicolon */
        }

        if(root != &elements[index]) {

        } else {
            /* special case for root semicolon */
        }
    }
}

void
parse_and_execute (Element *elements)
{
    
}