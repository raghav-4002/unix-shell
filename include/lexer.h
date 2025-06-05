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
    COMMAND,
    LOGIC_OR,
    LOGIC_AND,
    SEMICOLON,
    NIL,
} Element_Type;

/*
 * Data structures to represent a single element.

 * An element is just a struct with an element type,
   command, command_size, return_value.

 * If element type is `COMMAND`, then the element is a struct
   which has an array of string(`command`), such as 
   {"ls", "-a", "-l", NULL}. The purpose of `NULL` is 
   to tell that command ends here.

   Here `command_size` would be `4`, as there are `4` 
   elements in this array of strings.

   Here `return_value` would be `RETURN_SUCCESS`, as
   `ls` is a valid command with valid arguments.

 * If element type is `LOGIC_OR` (`||`), then the element 
   is a struct with `command` as `NULL`, and `command_size`
   as `0`.

   This is done because the term `LOGIC_OR` itself is
   enough to tell what the operand is, so there is no
   need to create an array of strings.

   Here, `return_value` will be the net return value
   of the logical or operation.

*/

typedef struct {
    Element_Type element_type;
    char **command;
    int return_value;
} Element;


Element *tokenize(char *raw_input, size_t *total_elements);


#endif