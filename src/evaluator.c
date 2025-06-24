#include "../include/evaluator.h"

/* Creating a stack data structure */
typedef struct stack
{
  Element element;
  struct stack *prev;
} Stack;

/* Represents the most recent item of stack */
Stack *top = NULL;

/*
 * Pushs an item of type `Element` to stack
 */
void
stack_push (Element element)
{
  if (!top)
    {
      top = malloc (sizeof (*top));
      top->prev = NULL;
    }
  else
    {
      Stack *ptr = malloc (sizeof (*ptr));
      ptr->prev = top;
      top = ptr;
    }

  top->element = element;
}

/*
 * Returns the `element` from top of stack.
 * Frees the memory associated with the top.
 */
Element
stack_pop()
{
  Element element = top->element;
  Stack *ptr = top;

  top = top->prev;
  free(ptr);

  return element;
}

void
evaluate (Element *ast_root)
{
  // evaluates the expression and executes each command
}
