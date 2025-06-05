#ifndef TOKENIZATION_H
#define TOKENIZATION_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


enum return_values {
    RETURN_SUCCESS  =  1,
    RETURN_FAILURE  = -1,
    NOT_DEFINED_YET =  0,
};


typedef enum {
    COMMAND,    /* like `ls -al` */
    LOGIC_OR,   /* `||` */
    LOGIC_AND,  /* `&&` */
    SEMICOLON,  /* `;` */
    NIL,        /* No type */
} Element_Type;

/*
 * A data structure to represent an element.
 
 * An element has a type (like a `COMMAND`,
   an operator like `LOGIC_AND` or `LOGIC_OR`).

 * If the `element_type` is `COMMAND`, then it 
   contains a string array (`command`) which 
   represents the command itself along with its 
   arguments.

   For ex: If the user enters `ls -al`, then 
   an element will be created of type `COMMAND`

   This element will have an array of strings
   `{"ls", "-al", NULL}`, where the first string
   is the command and the subsequent strings are
   the arguments of the command.

   This array has `NULL` as its last element.
   This is done in order to tell that the command
   has no more arguments.

  * If `&&` (logical and) is encountered while 
    tokenizing user input, then an element of
    type `LOGIC_AND` will be created.

    Same can be said if `||` or `;` are encountered.
    But in that case an element of type `LOGIC_OR`
    or `SEMICOLON` will be created respectively.

    These special elements don't need to have
    an array of strings, as they convey a 
    different meaning.

  * Every element also has a `return_value` which
    is initialized with `NOT_DEFINED_YET` for every
    newly created element, and only has meaning
    during parsing of these elements.

*/

typedef struct {
    Element_Type element_type;
    char **command;
    int return_value;
} Element;


Element *tokenize(char *raw_input, size_t *total_elements);


#endif