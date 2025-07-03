#ifndef TOKENIZATION_H
#define TOKENIZATION_H

#include <unistd.h>

/* Recognised tokens in the current grammar */
typedef enum Token_type
{
  COMMAND,     /* like `ls -al` */

  PIPE,        /* `|` */
  BG_OPERATOR, /* `&` */

  LEFT_PAREN,  /* `(` */
  RIGHT_PAREN, /* `)` */

  LOGIC_OR,    /* `||` */
  LOGIC_AND,   /* `&&` */
  NEXT,        /* `;` */
  
  NIL,         /* no type - used in the last token in `Token` array */

} Token_type;

/*
 * `Return_status` will be used to decide whether
 * to execute next command in a chain of operators
 * and commands
 */
typedef enum Return_status
{
  RETURN_SUCCESS =  0,
  RETURN_FAILURE =  1,
  NOT_DEFINED    = -1,

} Return_status;

typedef struct Token
{
  Token_type type;

  /*
   * `argv`: array of strings; first string is a command,
   *  subsequent strings are it's arguments.
   *  Last element of array is `NULL`.

   * `argc`: count of number of elements in `argv` array.

   * These two fields are only applicable for token of type
   * `COMMAND`. For the rest of the tokens, `argv` = `NULL`
   * and `argc` = 0
   */
  char **argv;
  size_t argc;

  struct Token *left;  /* left child of the token in an AST */
  struct Token *right; /* right child. AST: Abstract Syntax Tree */

  /*
   * Status of whether the `COMMAND` was successful or not.

   * For `LOGIC_AND` and `LOGIC_OR` tokens, it will be the net
   * status of both of its children.

   * For all other tokens, it will be `NOT_DEFINED`
   */
  Return_status return_status;

} Token;

/* Actual tokenizer function */
Token *tokenize(char *string);

#endif
