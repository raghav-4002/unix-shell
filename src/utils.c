#include "../include/utils.h"

/*
 * This function frees the memory allocated to elements of an array
   and the array itself.
*/
void
free_array_of_arrays (char **array, size_t array_size)
{
  /* free individual element */
  for (size_t i = 0; i < array_size; i++)
    {
      free (array[i]);
    }

  /* free the array */
  free (array);
  array = NULL;
}

void
free_elements (Element *elements)
{
  for (size_t i = 0; (elements)[i].element_type != NIL; i++)
    {
      if ((elements)[i].element_type == COMMAND)
        {
          for (size_t j = 0; (elements)[i].tokens[j] != NULL; j++)
            {
              free ((elements)[i].tokens[j]);
            }
          free ((elements)[i].tokens);
        }
    }

  free (elements);
}

void
traverse_ast (Element *ast_root)
{
  if (ast_root == NULL)
    return;

  traverse_ast (ast_root->left);

  if (ast_root->element_type == COMMAND)
    {
      for (size_t j = 0; ast_root->tokens[j] != NULL; j++)
        {
          printf ("%s ", ast_root->tokens[j]);
        }
      printf ("\n");
    }
  else if (ast_root->element_type == LOGIC_AND)
    {
      printf ("LOGIC AND\n");
    }
  else if (ast_root->element_type == LOGIC_OR)
    {
      printf ("LOGIC OR\n");
    }
  else if (ast_root->element_type == NEXT)
    {
      printf ("NEXT\n");
    }

  traverse_ast (ast_root->right);
}
