#include "../include/evaluator.h"
#include "../include/builtin_handling.h"
#include "../include/exec_handling.h"

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
execute(Element *node)
{
  if (is_builtin(node)) {
    handle_builtin(node);
  } else {
    handle_exec(node);
  }
}

/* 
 * Handles nodes of type `LOGIC_AND` and `LOGIC_OR` by checking
 * the return values of left child and executing right child accordingly.
 */
void
handle_logic_operator(Element *operator)
{
  Return_value left_return_val = operator->left->return_value;

  /* 0 and (anyting) = 0 */
  if(left_return_val == RETURN_FAILURE && operator->element_type == LOGIC_AND) {
    operator->return_value = RETURN_FAILURE;
    return;
  }

  /* 1 or (anyting) = 1 */
  if(left_return_val == RETURN_SUCCESS && operator->element_type == LOGIC_OR) {
    operator->return_value = RETURN_SUCCESS;
    return;
  }

  /* Only execute the right child of operator if both above conditions fail */
  execute(operator->right);
  Return_value right_return_val = operator->right->return_value;

  operator->return_value = right_return_val;
}

/* Traverses through the AST and exectues commands */
void
evaluate (Element *root)
{
  Element *node = root;

  /* Push nodes to stack until node of type `COMMAND` is not found */
  while(node->element_type != COMMAND) {
    stack_push(node);
    node = node->left;
  }

  execute(node);

  /* Start popping from the stack */
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
