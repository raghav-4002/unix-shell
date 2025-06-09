#include "../include/parser.h"
#include <stddef.h>

void
parse_pipeline(void)
{

}

Element *
parse_condition(Element *elements, size_t lower_lim, size_t upper_lim)
{

}

Element *
parse_sequence(Element *elements)
{
    /* logic to find positions of semicolons */
    size_t position_of_colons[100];
    size_t index = 1;
    size_t i, nil_index;

    for(i = 0; elements[i].element_type != NIL; i++) {
        if(elements[i].element_type == NEXT) {
            position_of_colons[index] = i;
            index++;
        }
    }
    nil_index = i;

    /* the last semi colon will be root */
    Element *root = &elements[index];

    /* now create a tree out of these semicolons */
    while(index != 0) {

        size_t lower_lim, upper_lim;

        /* for left child */
        if(index != 1) {
            elements[index].left = &elements[index - 1];
        } else {
            /* special case for the first semicolon */
            lower_lim = 0, upper_lim = position_of_colons[index];
            elements[index].left = parse_condition(elements, lower_lim, upper_lim);
        }

        /* for right child */
        if(root != &elements[index]) {
            lower_lim = position_of_colons[index] + 1, upper_lim = position_of_colons[index + 1];
            elements[index].right = parse_condition(elements, lower_lim, upper_lim);
        } else {
            /* special case for root semicolon */
            lower_lim = position_of_colons[index] + 1, upper_lim = nil_index;
            elements[index].right = parse_condition(elements, lower_lim, upper_lim);
        }

        index--;
    }

    return root;
}

void
parse_and_execute (Element *elements)
{
    parse_sequence(elements);
}