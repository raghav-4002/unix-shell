#include "../include/parser.h"
#include <stddef.h>

#define MAX_ALLOWED_SIZE 100

Element *
parse_pipeline(Element *elements, size_t from, size_t till)
{

}

/* this function will parse the conditions from `lower_limit` to `upper_limit` of `elements` */
Element *
parse_condition(Element *elements, size_t from, size_t till)
{
    size_t position_of_operands[MAX_ALLOWED_SIZE];
    size_t index = 1;
    size_t i, last_index;

    for(i = from; i <= till; i++) {
        if (
            elements[i].element_type == LOGIC_AND ||
            elements[i].element_type == LOGIC_OR
        ) {
            position_of_operands[index] = i;
            index++;
        }
    }

    last_index = i;

    /* the last operand/condition will be root */
    Element *root = &elements[index];

    while(index != 0) {
        size_t lower_lim, upper_lim;

        /* for left child */
        if(index != 1) {
            elements[index].left = &elements[index - 1];
        } else {
            /* special case for the first operand */
            lower_lim = from;
            upper_lim = position_of_operands[index];
            elements[index].left = parse_pipeline(elements, lower_lim, upper_lim);
        }

        /* for right child */
        if(root != &elements[index]) {
            lower_lim = position_of_operands[index] + 1;
            upper_lim = position_of_operands[index + 1];
            elements[index].right = parse_pipeline(elements, lower_lim, upper_lim);
        } else {
            /* special case for last (`root`) semicolon */
            lower_lim = position_of_operands[index] + 1;
            upper_lim = last_index;
            elements[index].right = parse_pipeline(elements, lower_lim, upper_lim);
        }

        index--;
    }

    return root;
}

Element *
parse_sequence(Element *elements)
{
    /* logic to find positions of semicolons */
    size_t position_of_colons[MAX_ALLOWED_SIZE];
    size_t index = 1;
    size_t i, last_index;

    for(i = 0; elements[i].element_type != NIL && i < MAX_ALLOWED_SIZE; i++) {
        if(elements[i].element_type == NEXT) {
            position_of_colons[index] = i;
            index++;
        }
    }

    if(i >= MAX_ALLOWED_SIZE) return NULL;

    last_index = i;

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
            lower_lim = 0;
            upper_lim = position_of_colons[index];
            elements[index].left = parse_condition(elements, lower_lim, upper_lim);
        }

        /* for right child */
        if(root != &elements[index]) {
            lower_lim = position_of_colons[index] + 1;
            upper_lim = position_of_colons[index + 1];
            elements[index].right = parse_condition(elements, lower_lim, upper_lim);
        } else {
            /* special case for last (`root`) semicolon */
            lower_lim = position_of_colons[index] + 1;
            upper_lim = last_index;
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