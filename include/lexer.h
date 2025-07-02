#ifndef TOKENIZATION_H
#define TOKENIZATION_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Token_type
{
  COMMAND,     /* like `ls -al` */

  PIPE,        /* '|' */
  BG_OPERATOR, /* '&' */

  LOGIC_OR,    /* `||` */
  LOGIC_AND,   /* `&&` */
  NEXT,        /* `;` */

  NIL,         /* No type */

} Token_type;

typedef enum Return_status
{
  RETURN_SUCCESS  =  0,
  RETURN_FAILURE  =  1,
  NOT_DEFINED_YET = -1,

} Return_status;

typedef struct Token
{
  Token_type type;

  char **args;                 /* relevent only for `element_type` `COMMAND` */

  struct Token *left;        /* left child in abstract syntax tree */
  struct Token *right;       /* right child in the same tree */

  Return_status return_status; /* relevent only while executing */

} Token;

Token *tokenize (char *raw_input);

#endif
