#include "../include/evaluator.h"
#include "../include/builtin_handling.h"
#include "../include/exec_handling.h"

/* =================== Stack ========================= */

/* Creating a stack data structure */
typedef struct stack
{
  Token *token;
  struct stack *prev;
} Stack;

/* Represents the most recent item of stack */
Stack *top = NULL;

/*
 * Pushs an item of type `Element` to stack
 */
int
stack_push (Token *token)
{
  if (!top)
    {
      top = malloc (sizeof (*top));

      if (top == NULL)
        {
          /* memory allocation failed */
          return -1;
        }
      top->prev = NULL;
    }
  else
    {
      Stack *ptr = malloc (sizeof (*ptr));

      if (top == NULL)
        {
          return -1;
        }

      ptr->prev = top;
      top = ptr;
    }

  top->token = token;

  return 0;
}

/*
 * Returns the `element` from top of stack.
 * Frees the memory associated with the top.
 */
Token *
stack_pop ()
{
  Token *token = top->token;
  Stack *ptr = top;

  top = top->prev;
  free (ptr);

  return token;
}

/* ================= Evaluation =======================*/

void
handle_command (Token *node)
{
  if (!handle_builtin (node))
    {
      handle_exec (node);
    }
}

/*
 * Handles nodes of type `LOGIC_AND` and `LOGIC_OR` by checking
 * the return values of left child and executing right child accordingly.
 */
void
handle_logic_operator (Token *operator)
{
  Return_status left_return_val = operator->left->return_status;

  /* 0 and (anyting) = 0 */
  if (left_return_val == RETURN_FAILURE && operator->type == LOGIC_AND)
    {
      operator->return_status = RETURN_FAILURE;
      return;
    }

  /* 1 or (anyting) = 1 */
  if (left_return_val == RETURN_SUCCESS && operator->type == LOGIC_OR)
    {
      operator->return_status = RETURN_SUCCESS;
      return;
    }

  /* Only execute the right child of operator if both above conditions fail */
  handle_command (operator->right);
  Return_status right_return_val = operator->right->return_status;

  operator->return_status = right_return_val;
}

/* Traverses through the AST and exectues commands */
void
evaluate (Token *root)
{
  Token *node = root;

  /* Push nodes to stack until node of type `COMMAND` is not found */
  while (node->type != COMMAND)
    {
      int return_val = stack_push (node);

      /* memory allocation fails */
      if (return_val == -1)
        {
          fprintf (stderr, "Encountered some error...\n");

          /* Free allocated memory */
          while (top)
            {
              stack_pop ();
            }

          return;
        }

      node = node->left;
    }

  handle_command (node);

  /* Start popping from the stack */
  while (top != NULL)
    {
      Token *operator = stack_pop ();

      switch (operator->type)
        {
        case LOGIC_AND:
        case LOGIC_OR:
          handle_logic_operator (operator);
          break;

        case NEXT:
          node = operator->right;
          evaluate (node);

          break;
        }
    }
}
