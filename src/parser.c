#include "../include/parser.h"

Element *
parse_condition(Element *elements, size_t *pos)
{

}

Element *
parse_sequence(Element *elements, size_t pos)
{
    Element *left = parse_condition(elements, &pos);

    while(elements[pos].element_type != NIL) {
        elements[pos].left = left;
        left = &elements[pos];
        pos++;
        elements[pos].right = parse_condition(elements, &pos);
    }

    Element *ast_root = left;

    return ast_root;
}

void
parse_and_evaluate (Element *elements)
{
    size_t pos = 0;
    Element *ast_root = parse_sequence(elements, pos);     
}