#include "../include/parser.h"

Element *
parse_condition(Element *elements, size_t *pos)
{
    Element *left = &elements[*pos];
    (*pos)++;

    while(elements[*pos].element_type != NIL &&
          elements[*pos].element_type != NEXT) {

        elements[*pos].left = left;
        left = &elements[*pos];
        (*pos)++;
        left->right = &elements[*pos];
        (*pos)++;
    }

    Element *root = left;

    return root;
}

Element *
parse_sequence(Element *elements)
{
    size_t pos = 0;

    Element *left = parse_condition(elements, &pos);

    while(elements[pos].element_type != NIL) {
        elements[pos].left = left;
        left = &elements[pos];
        pos++;
        left->right = parse_condition(elements, &pos);
    }

    Element *ast_root = left;

    return ast_root;
}

void
parse_and_evaluate (Element *elements)
{
    Element *ast_root = parse_sequence(elements);     
}