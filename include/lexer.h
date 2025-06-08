#ifndef TOKENIZATION_H
#define TOKENIZATION_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum return_values
{
  RETURN_SUCCESS = 1,
  RETURN_FAILURE = -1,
  NOT_DEFINED_YET = 0,
};

typedef enum
{
  COMMAND, /* like `ls -al` */

  PIPE,        /* '|' */
  BG_OPERATOR, /* '&' */

  LOGIC_OR,  /* `||` */
  LOGIC_AND, /* `&&` */

  NEXT, /* `;` */

  NIL, /* No type */
} Element_Type;

typedef struct
{
  Element_Type element_type;
  char **tokens;
  int return_value;
} Element;

Element *tokenize (char *raw_input);

#endif