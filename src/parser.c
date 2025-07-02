#include "../include/parser.h"
#include "../include/evaluator.h"

Token *
parse_condition (Token *tokens, size_t *pos)
{
  Token *left = &tokens[*pos];

  if (left->type != COMMAND)
    {
      /* `left` must always be an `element` of type `COMMAND` */
      fprintf (stderr, "Invalid syntax...\n");
      return NULL;
    }

  while (tokens[*pos].type != NIL
         && tokens[*pos].type != NEXT)
    {

      if (tokens[*pos].type == LOGIC_AND
          || tokens[*pos].type == LOGIC_OR)
        {
          Token *parent = &tokens[*pos];
          parent->left = left;

          /* Move to the next child */
          (*pos)++;

          parent->right = &tokens[*pos];

          if (parent->right->type != COMMAND)
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

  Token *root = left;

  return root;
}

Token *
parse_sequence (Token *tokens)
{
  size_t pos = 0;
  Token *left = parse_condition (tokens, &pos);

  /* In case of error */
  if (!left)
    return NULL;

  while (tokens[pos].type != NIL)
    {
      Token *parent = &tokens[pos];
      parent->left = left;

      /* move to next child */
      pos++;

      parent->right = parse_condition (tokens, &pos);
      if (!parent->right)
        return NULL;

      /* Current parent becomes left child of next parent */
      left = parent;
    }

  Token *ast_root = left;

  return ast_root;
}

void
parse_and_evaluate (Token *tokens)
{
  Token *ast_root = parse_sequence (tokens);

  if (ast_root)
    evaluate (ast_root);
}
