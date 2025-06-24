#include "../include/parser.h"
#include "../include/evaluator.h"

Element *
parse_condition (Element *elements, size_t *pos)
{
  Element *left = &elements[*pos];

  if (left->element_type != COMMAND)
    {
      /* `left` must always be an `element` of type `COMMAND` */
      fprintf (stderr, "Invalid syntax...\n");
      return NULL;
    }

  while (elements[*pos].element_type != NIL
         && elements[*pos].element_type != NEXT)
    {

      if (elements[*pos].element_type == LOGIC_AND
          || elements[*pos].element_type == LOGIC_OR)
        {
          Element *parent = &elements[*pos];
          parent->left = left;

          /* Move to the next child */
          (*pos)++;

          parent->right = &elements[*pos];

          if (parent->right->element_type != COMMAND)
            {
              /* right child must be of type `COMMAND` */
              fprintf (stderr, "Invalid syntax...\n");
              return NULL;
            }

          /* Current parent becomes the left child of next parent */
          left = parent;
        }

      (*pos)++;
    }

  Element *root = left;

  return root;
}

Element *
parse_sequence (Element *elements)
{
  size_t pos = 0;
  Element *left = parse_condition (elements, &pos);

  /* In case of error */
  if (!left)
    return NULL;

  while (elements[pos].element_type != NIL)
    {
      Element *parent = &elements[pos];
      parent->left = left;

      /* move to next child */
      pos++;

      parent->right = parse_condition (elements, &pos);
      if (!parent->right)
        return NULL;

      /* Current parent becomes left child of next parent */
      left = parent;
    }

  Element *ast_root = left;

  return ast_root;
}

void
parse_and_evaluate (Element *elements)
{
  Element *ast_root = parse_sequence (elements);

  if (ast_root)
    evaluate (ast_root);
}
