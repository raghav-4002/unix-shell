#include "../include/evaluator.h"

/* =================== Stack ========================= */

/* Creating a stack data structure */
typedef struct stack
{
  Element *element;
  struct stack *prev;
} Stack;

/* Represents the most recent item of stack */
Stack *top = NULL;

/*
 * Pushs an item of type `Element` to stack
 */
void
stack_push (Element *element)
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
Element *
stack_pop()
{
  Element *element = top->element;
  Stack *ptr = top;

  top = top->prev;
  free(ptr);

  return element;
}

/* ================= Evaluation =======================*/

void
handle_logic_operator(Element *operator)
{

}

void
evaluate (Element *root)
{
  Element *node = root;

  while(node->element_type != COMMAND) {
    stack_push(node);
    node = node->left;
  }

  //execute node;

  while(top != NULL) {
    Element *operator = stack_pop();

    switch(operator->element_type) {
      case LOGIC_AND: case LOGIC_OR:
        handle_logic_operator(operator);
        break;

      case NEXT:
        node = operator->right;
        evaluate(node);

        break;
    }
  }
}
