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
  int left_return_val = operator->left->return_value;

  if(left_return_val == RETURN_FAILURE && operator->element_type == LOGIC_AND) {
    operator->return_value = 0;
    return;
  }

  if(left_return_val == RETURN_SUCCESS && operator->element_type == LOGIC_OR) {
    operator->return_value = 1;
    return;
  }

  // execute right child and get it's return value in right_return_val
  int right_return_val;

  operator->return_value = right_return_val;
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
