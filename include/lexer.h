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

  ROOT, /* a custom element acting as the root of an AST */
  NIL,  /* No type */
} Element_Type;

/*
 * After passing the input to the lexer, the
   lexer returns an array of type `Element`.

 * An `Element` is just a categorized user input.

 * For eg, if the user inputs `ls -al && cd ; cat file | less`,
   then the lexer will return an array of `Elements` with
   each `Element` the following type:
   - `COMMAND` => `ls -al`
   - `LOGIC_AND` => `&&`
   - `COMMAND` => `cd`
   - `NEXT` => `;`
   - `COMMAND` => `cat file`
   - `PIPE` => `|`
   - `COMMAND` => `less`

 * The advantage of using such a structure is that when
   this array will be passed to the parser, the
   parser will have to do comparatively less work.
*/

typedef struct Element
{
  Element_Type element_type;
  char **tokens; /* relevent only for `element_type` `COMMAND` */

  struct Element *left;  /* left child in abstract syntax tree */
  struct Element *right; /* right child in the same tree */

  int return_value; /* relevent only while executing */
} Element;

Element *tokenize (char *raw_input);

#endif