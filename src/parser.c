#include "../include/parser.h"

Element *
parse_condition (Element *elements, size_t *pos)
{
  Element *left = &elements[*pos];

  while (elements[*pos].element_type != NIL
         && elements[*pos].element_type != NEXT)
    {

      if (elements[*pos].element_type == LOGIC_AND
          || elements[*pos].element_type == LOGIC_OR)
        {

          elements[*pos].left = left;
          left = &elements[*pos];
          (*pos)++;
          left->right = &elements[*pos];
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

  /* left most leaf */
  Element *left = parse_condition (elements, &pos);

  /* `parse_condition()` will increment `pos` */
  while (elements[pos].element_type != NIL)
    {
      elements[pos].left = left;
      left = &elements[pos];
      pos++;
      left->right = parse_condition (elements, &pos);
    }

  Element *ast_root = left;

  return ast_root;
}

void
traverse(Element *ast_root)
{
    if(ast_root == NULL) return;

    traverse(ast_root->left);

    if(ast_root->element_type == COMMAND) {
        for (size_t j = 0; ast_root->tokens[j] != NULL; j++) {
            printf("%s ", ast_root->tokens[j]);
        }
        printf("\n");
    }
    else if(ast_root->element_type == LOGIC_AND) {
        printf("LOGIC AND\n");
    }
    else if(ast_root->element_type == LOGIC_OR) {
        printf("LOGIC OR\n");
    }
    else if(ast_root->element_type == NEXT) {
        printf("NEXT\n");
    }

    traverse(ast_root->right);
}

void
parse_and_evaluate (Element *elements)
{
  Element *ast_root = parse_sequence (elements);

  traverse(ast_root);
}