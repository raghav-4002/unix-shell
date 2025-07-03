#include <stdio.h>

#include "../include/utils.h"

void
free_tokens (Token *tokens)
{
  for (size_t i = 0; (tokens)[i].type != NIL; i++)
    {
      if ((tokens)[i].type == COMMAND)
        {
          // for (size_t j = 0; (tokens)[i].argv[j] != NULL; j++)
          //   {
          //     free ((tokens)[i].argv[j]);
            // }
          // free ((tokens)[i].argv);
        }
    }

  free (tokens);
}

void
traverse_ast (Token *ast_root)
{
  if (ast_root == NULL)
    return;

  traverse_ast (ast_root->left);

  if (ast_root->type == COMMAND)
    {
      for (size_t j = 0; ast_root->argv[j] != NULL; j++)
        {
          printf ("%s ", ast_root->argv[j]);
        }
      printf ("\n");
    }
  else if (ast_root->type == LOGIC_AND)
    {
      printf ("LOGIC AND\n");
    }
  else if (ast_root->type == LOGIC_OR)
    {
      printf ("LOGIC OR\n");
    }
  else if (ast_root->type == NEXT)
    {
      printf ("NEXT\n");
    }

  traverse_ast (ast_root->right);
}
